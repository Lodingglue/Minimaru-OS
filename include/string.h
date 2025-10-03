#ifndef STRING_H
#define STRING_H

#include "types.h"

int strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, uint32_t n);
void strncpy(char *dest, const char *src, uint32_t n);

#endif