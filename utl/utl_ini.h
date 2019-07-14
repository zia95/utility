#ifndef UTL_INI
#define UTL_INI


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utl_mem.h"
#include "utl_file.h"

#ifndef COMMENT_CHARS_DEFAULT
#define COMMENT_CHARS_DEFAULT ";#"
#endif // !COMMENT_CHARS_DEFAULT

#ifndef COMMENT_WCHARS_DEFAULT
#define COMMENT_WCHARS_DEFAULT L";#"
#endif // !COMMENT_WCHARS_DEFAULT



typedef struct INI_FILEA
{
	FILE* strm;
	const char* cmnt_chars;
	char* buff_line;
}INIFileA_t, * PINIFileA_t;

typedef struct INI_FILEW
{
	FILE* strm;
	const wchar_t* cmnt_chars;
	wchar_t* buff_line;
}INIFileW_t, * PINIFileW_t;

typedef struct INI_PARSE_LINE_RESULTA
{
	char* pSection;
	char* pKey;
	char* pValue;
}INIParseLineResultA_t, * PINIParseLineResultA_t;

typedef struct INI_PARSE_LINE_RESULTW
{
	wchar_t* pSection;
	wchar_t* pKey;
	wchar_t* pValue;
}INIParseLineResultW_t, * PINIParseLineResultW_t;




PINIFileA_t ini_newa(FILE* stream);
PINIFileW_t ini_neww(FILE* stream);

#define ini_new_filea(file) ini_newa(file_opena(file, "r"))
#define ini_new_filew(file) ini_neww(file_openw(file, L"r"))

#define ini_comment_chars(pInifile) pInifile->cmnt_chars 
//#define ini_comment_charsw(pInifilew) ini_comment_chars(pInifilew)

#define ini_stream(pInifilew) pInifilew->strm


bool ini_closea(PINIFileA_t file);
bool ini_closew(PINIFileW_t file);

bool ini_readlinea(PINIFileA_t file);
bool ini_readlinew(PINIFileW_t file);

bool ini_parselinea(PINIFileA_t file, PINIParseLineResultA_t result);
bool ini_parselinew(PINIFileW_t file, PINIParseLineResultW_t result);






#ifdef UNICODE
#define INIFile_t	INIFileW_t
#define PINIFile_t	PINIFileW_t

#define INIParseLineResult_t	INIParseLineResultW_t
#define PINIParseLineResult_t	PINIParseLineResultW_t

#define ini_new			ini_neww
#define ini_new_file	ini_new_filew

#define ini_close		ini_closew

#define ini_readline	ini_readlinew

#define ini_parseline	ini_parselinew

#else

#define INIFile_t	INIFileA_t
#define PINIFile_t	PINIFileA_t

#define INIParseLineResult_t	INIParseLineResultA_t
#define PINIParseLineResult_t	PINIParseLineResultA_t

#define ini_new			ini_newa
#define ini_new_file	ini_new_filea

#define ini_close		ini_closea

#define ini_readline	ini_readlinea

#define ini_parseline	ini_parselinea
#endif // UNICODE


#endif