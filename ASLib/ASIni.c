#include "ASIni.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#if defined(_MSC_VER)
// Remove warnings from Level 4
#pragma warning (disable : 4244)
#pragma warning (disable : 4514)
#pragma warning (disable : 4706)
#endif

static const int INI_SIZE_INCREMENT = 10; // increment of memory allocation

typedef struct
{
  char*           value_name;
  char*           value;
}
ini_value_t;

typedef struct
{
  char*           key_name;
  int             value_count;
  int             current_size;
  ini_value_t*    values;
}
ini_key_t;

typedef struct
{
  ini_key_t*      ini;
  int             key_count;
  int             current_size;
}
ASIni, *PASIni;

char* ASIni_trim(char *str)
{
  int pos = 0;
  char *dest = str;

  // skip leading blanks
  while (str[pos] <= ' ' && str[pos] > 0)
    pos++;

  while (str[pos])
  {
    *(dest++) = str[pos];
    pos++;
  }

  *(dest--) = '\0'; // store the null

  // remove trailing blanks
  while (dest >= str && *dest <= ' ' && *dest > 0)
    *(dest--) = '\0';

  return dest;
}

// set the value in ini file
int ASIni_set(ASHANDLE hIni, const char *key, const char *value, const char *set)
{
  PASIni self = (PASIni)hIni;
  ini_key_t *pKey = NULL;
  ini_value_t *pValue = NULL;
  int i;

  if (self == NULL)
  {
    return 0;
  }


  for (i = 0; i < self->key_count; i++)
  {
    if (strcasecmp(self->ini[i].key_name, key) == 0)
    {
      pKey = &self->ini[i];
      break;
    }
  }

  // if this is a new key, try to allocate memory for it
  if (pKey == NULL) {
    self->key_count++;

    // if we don't have enough room for this new key, try to allocate more memory
    if (self->key_count > self->current_size) {
      self->current_size += INI_SIZE_INCREMENT;
      if (self->ini)
      {
        self->ini = (ini_key_t *)realloc(self->ini, sizeof(ini_key_t) * self->current_size);
      }
      else
      {
        self->ini = (ini_key_t *)malloc(sizeof(ini_key_t) * self->current_size);
      }

      if (!self->ini)
      {
        return 0;
      }
    }

    pKey = &self->ini[self->key_count - 1];
    pKey->key_name = strdup(key);
    pKey->values = NULL;
    pKey->value_count = 0;
    pKey->current_size = 0;
  }

  if (pValue == NULL)
  {
    for (i = 0; i < pKey->value_count; i++)
    {
      if (strcasecmp(value, pKey->values[i].value_name) == 0)
      {
        pValue = &pKey->values[i];
        break;
      }
    }
  }

  if (pValue != NULL) {
    // this value already exists in the key...
    free(pValue->value);
    pValue->value = strdup(set);

    if (pValue->value == NULL)
    {
      return 0;
    }
  }
  else
  {
    pKey->value_count++;

    if (pKey->value_count > pKey->current_size) {
      pKey->current_size += INI_SIZE_INCREMENT;
      if (pKey->values) {
        pKey->values = (ini_value_t *)realloc(pKey->values, sizeof(ini_value_t) * pKey->current_size);
      } else {
        pKey->values = (ini_value_t *)malloc(sizeof(ini_value_t) * pKey->current_size);
      }

      if (pKey->values == NULL)
      {
        return 0;
      }
    }

    pKey->values[pKey->value_count - 1].value_name = strdup(value);
    pKey->values[pKey->value_count - 1].value = strdup(set);

    if (pKey->values[pKey->value_count - 1].value == NULL ||
        pKey->values[pKey->value_count - 1].value_name == NULL)
    {
      return 0;
    }

    ASIni_trim(pKey->values[pKey->value_count - 1].value);
    ASIni_trim(pKey->values[pKey->value_count - 1].value_name);
  }

  return 1;
}

ini_key_t* ASIni_get_key(ASHANDLE hIni, const char *key)
{
  PASIni self = (PASIni)hIni;
  int i;

  if (self == NULL)
  {
    return NULL;
  }

  for (i = 0; i < self->key_count; i++)
  {
    if (strcasecmp(self->ini[i].key_name, key) == 0)
    {
      return &self->ini[i];
    }
  }

  return NULL;
}

const char* ASIni_get_value(ASHANDLE hIni, const char *key, const char *value, const char* def)
{
  ini_key_t *pKey = ASIni_get_key(hIni, key);
  int i;

  if (pKey != NULL)
  {
    for (i = 0; i < pKey->value_count; i++)
    {
      if (strcasecmp(pKey->values[i].value_name, value) == 0)
      {
        return pKey->values[i].value;
      }
    }
  }

  return def;
}

int ASIniSave(ASHANDLE hIni, const char *filename)
{
  PASIni self = (PASIni)hIni;
  FILE *fp = NULL;
  int i, j;

  if (self == NULL)
  {
    return 0;
  }

  fp = fopen(filename, "w");
  if (fp == NULL)
  {
    return 0;
  }

  for (i = 0; i < self->key_count; i++)
  {
    fprintf(fp, "[%s]\n", self->ini[i].key_name);

    for (j = 0; j < self->ini[i].value_count; j++)
    {
      fprintf(fp, "%s=%s\n", self->ini[i].values[j].value_name, self->ini[i].values[j].value);
    }

    fprintf(fp, "\n");
  }

  fclose(fp);
  return 1;
}

ASHANDLE ASIniLoad(const char *filename)
{
  ASIni* self = NULL;
  FILE *fp = NULL;
  int c;
  char str[256], section[256];

  self = (ASIni*) malloc(sizeof(ASIni));
  if (NULL == self)
  {
    return NULL;
  }
  memset(self, 0, sizeof(ASIni));

  fp = fopen(filename, "r");
  if (NULL == fp)
  {
    return NULL;
  }

  c = fgetc(fp);
  if (0xEF == c)
  {
    fgetc(fp);
    fgetc(fp);
  }
  else
  {
    ungetc(c, fp);
  }

  section[0] = '\0';

  while (fgets(str, 256, fp))
  {
    ASIni_trim(str); // trim all the blanks or linefeeds

    // skip all comment lines or empty lines
    if (!str[0] || str[0] == ';' || str[0] == '/' || str[0] == '#')
      continue;

    int length = strlen(str);
    char *p;

    // check if this is a session line (e.g., [SECTION])
    if (str[0] == '[' && str[length - 1] == ']')
    {
      strcpy(section, &str[1]);
      section[length - 2] = 0; // remove the ]

      ASIni_trim(section); // trim section name after removing []
    }
    else if ((p = strchr(str, '=')) != NULL)
    {
      *(p++) = '\0';
      ASIni_trim(str);
      char* end = ASIni_trim(p);
      if (p[0] == '\"' && end[0] == '\"')
      {
        p++;
        end[0] = '\0';
      }
      ASIni_set(self, section, str, p);
    }
  }

  fclose(fp);

  return (ASHANDLE)self;
}

const char* ASIniGetString(ASHANDLE hIni, const char *key, const char *value, const char* def)
{
  return ASIni_get_value(hIni, key, value, def);
}

int ASIniGetInt(ASHANDLE hIni, const char *key, const char *value, int def)
{
  const char* ret = ASIni_get_value(hIni, key, value, "");

  if (ret == NULL || *ret == '\0')
  {
    return def;
  }
  else
  {
    return atoi(ret);
  }
}

void ASIniClose(ASHANDLE hIni)
{
  PASIni self = (PASIni)hIni;
  int i, j;

  if (self == NULL)
  {
    return ;
  }

  if (self->ini)
  {
    for (i = 0; i < self->key_count; i++)
    {
      for (j = 0; j < self->ini[i].value_count; j++)
      {
        free(self->ini[i].values[j].value);
        free(self->ini[i].values[j].value_name);
      }

      free(self->ini[i].values);
      free(self->ini[i].key_name);
    }
    free(self->ini);
    self->ini = NULL;
  }

  free(self);
}

const char* ASIniGetValueNameByIndex(ASHANDLE hIni, const char *key, unsigned int index, const char* def)
{
  ini_key_t *pKey = ASIni_get_key(hIni, key);

  if (pKey != NULL)
  {
    if (index < pKey->value_count)
    {
      return pKey->values[index].value_name;
    }
  }

  return def;
}

const char* ASIniGetStringByIndex(ASHANDLE hIni, const char *key, unsigned int index, const char* def)
{
  ini_key_t *pKey = ASIni_get_key(hIni, key);

  if (pKey != NULL)
  {
    if (index < pKey->value_count)
    {
      return pKey->values[index].value;
    }
  }

  return def;
}

int ASIniGetIntByIndex(ASHANDLE hIni, const char *key, unsigned int index, int def)
{
  const char* ret = ASIniGetStringByIndex(hIni, key, index, "");

  if (ret == NULL || *ret == '\0')
  {
    return def;
  }
  else
  {
    return atoi(ret);
  }
}
