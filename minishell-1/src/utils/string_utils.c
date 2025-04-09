#include <stdlib.h>
#include <string.h>
#include "minishell.h"

char *ft_strjoin(const char *s1, const char *s2)
{
    char *result;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len = strlen(s);

    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    strcpy(dup, s);
    return dup;
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    char *substr;
    size_t s_len = strlen(s);

    if (start >= s_len)
        return ft_strdup("");
    if (len > s_len - start)
        len = s_len - start;

    substr = malloc(len + 1);
    if (!substr)
        return NULL;
    strncpy(substr, s + start, len);
    substr[len] = '\0';
    return substr;
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}