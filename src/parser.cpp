#include <string.h>

int HaveCommentary(const char *string)
{
    return (strchr(string, ';') != NULL);
}

char *StripCommentary(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i <= n && src[i] != ';' && src[i] != '\0' && src[i] != ' ' && src[i] != '\n'; i++)
        dest[i] = src[i];

    dest[i] = '\0';
    return dest;
}
