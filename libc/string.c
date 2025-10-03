#include "string.h"

int strlen(const char *str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == 0 || s2[i] == 0) {
            return *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
        }
    }
    return 0;
}

void strncpy(char *dest, const char *src, uint32_t n) {
    for (uint32_t i = 0; i < n && src[i] != 0; i++) {
        dest[i] = src[i];
    }
    for (; n > 0; n--) {
        dest[n - 1] = 0; 
    }
}