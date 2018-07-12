/*
 * filename: parser.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define NO_MATCH "i didn't understand that";
#define RET_ERR (char*)(-1)
#define RET_FAILED (char*)(-2)
#define INIT_OK 0
#define INIT_FAILED -1

static int reg_compiled = 0;

static pair_t parser_pairs[] = {
	{"question", "answer"},
	{"^give.*mehl", "mehl"},
	{0, 0}
};

int
parser_init()
{
	regex_t		*reg;
	int 		 i = 0;

	while(parser_pairs[i].q != 0)
	{
		reg = malloc(sizeof(regex_t));

		if (regcomp(reg, parser_pairs[i].q, 0)) 
		{
			return INIT_FAILED;
		}

		parser_pairs[i].r = reg;
		i++;
	}

	reg_compiled = 1;

	return INIT_OK;
}

char*
parse(char* s)
{
	regmatch_t      match;
	int			rc 	= 0,
				i	= 0;

	while(parser_pairs[i].q != 0)
	{
		if (!reg_compiled) 
		{
			if (parser_init())
			{
				return RET_FAILED;
			}
		}

		rc = regexec(parser_pairs[i].r ,s, 0, &match, 0);
		if (!rc) {
			return parser_pairs[i].a;
		}
		else
		{
		}

		i++;
	}

	/* No pair found */
	return NO_MATCH;
}
