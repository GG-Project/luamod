#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

int HaveChar(const char *buff, char charater);

int HaveCommentary(const char *string);

char *StripCommentary(char *dest, const char *src, size_t n);

#endif // PARSER_H
