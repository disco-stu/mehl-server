/*
 * filename: parser.h
 */

#include <regex.h>

#ifndef __PARSER_H_Y
#define __PARSER_H_Y

struct pair {
	char *q;
	char *a;
	regex_t	*r;
} typedef pair_t;

char* parse(char*);

#endif
