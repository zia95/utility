#ifndef UTL_CMDLN
#define UTL_CMDLN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strlen()
#include <ctype.h>//tolower()
#include <stdbool.h>//bool,true,false
//#include <tchar.h>


#include "utl.h"
#include "utl_str.h"

#ifdef CMDLN_NC
#define CMDLN_STR_CMP(X,Y)  str_cmpi(X,Y)
#define CMDLN_STR_CMPN(X,Y,L)  str_cmpni(X,Y,L)

#define CMDLN_STRW_CMP(X,Y)  strw_cmpi(X,Y)
#define CMDLN_STRW_CMPN(X,Y,L)  strw_cmpni(X,Y,L)
#else
#define CMDLN_STR_CMP(X,Y)  str_cmp(X,Y)
#define CMDLN_STR_CMPN(X,Y,L)  str_cmpn(X,Y,L)

#define CMDLN_STRW_CMP(X,Y)  strw_cmp(X,Y)
#define CMDLN_STRW_CMPN(X,Y,L)  strw_cmpn(X,Y,L)
#endif //!CMDLN_NC


typedef struct KEY_PAIRA
{
	char* key;
	char* val;
	int kidx;
} KeypairA_t, * PKeypairA_t;
typedef struct KEY_PAIRW
{
	wchar_t* key;
	wchar_t* val;
	int kidx;
} KeypairW_t, * PKeypairW_t;


typedef struct COMMAND_LINE_PARSERA
{
	int argc;
	char** argv;

	int sargc;
	char** sargv;

	int argc_idx;

	KeypairA_t result;
} CmdLnParserA_t, * PCmdLnParserA_t;
typedef struct COMMAND_LINE_PARSERW
{
	int argc;
	wchar_t** argv;

	int sargc;
	wchar_t** sargv;

	int argc_idx;

	KeypairW_t result;
} CmdLnParserW_t, * PCmdLnParserW_t;


PCmdLnParserA_t cmdln_parser_newa(int argc, char** argv, int sargc, const char** sargv);
PCmdLnParserW_t cmdln_parser_neww(int argc, wchar_t** argv, int sargc, const wchar_t** sargv);


#define cmdln_argv(pParser) pParser->argv
#define cmdln_argc(pParser) pParser->argc

#define cmdln_sargv(pParser) pParser->sargv
#define cmdln_sargc(pParser) pParser->sargc

#define cmdln_parser_get_result(pParser) &pParser->result
#define cmdln_parser_finished(pParser) !(pParser->argc_idx < pParser->argc)
#define cmdln_parser_free(pParser) free(pParser);
//#define cmdln_parser_free(pParser) if (pParser->buffer) { free(pParser->buffer); } free(pParser);

#define cmdln_curr_idx(pParser) pParser->argc_idx
#define cmdln_curr_arg(pParser) pParser->argv[cmdln_curr_idx(pParser)]
#define cmdln_first(pParser) (pParser->argc_idx = 0)
#define cmdln_reset cmdln_first
#define cmdln_next(pParser) (++pParser->argc_idx < pParser->argc)

PKeypairA_t cmdln_parsea(PCmdLnParserA_t pParser);
PKeypairW_t cmdln_parsew(PCmdLnParserW_t pParser);


#ifdef UNICODE
#define cmdln_parser_new cmdln_parser_neww
#define cmdln_parse cmdln_parsew
#else
#define cmdln_parser_new cmdln_parser_newa
#define cmdln_parse cmdln_parsea
#endif // UNICODE


#endif // !UTL_CMDLN
