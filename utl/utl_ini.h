#ifndef UTL_INI
#define UTL_INI


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utl_mem.h"
#include "utl_file.h"

#ifndef DEF_CMNT_CHAR
#define DEF_CMNT_CHAR ";#"
#endif // !DEF_CMNT_CHAR

#ifndef DEF_CMNT_CHARW
#define DEF_CMNT_CHARW L";#"
#endif // !DEF_CMNT_CHARW



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




PINIFileA_t ini_newa(FILE* stream)
{
	if (!stream)
		return NULL;
	
	INIFileA_t* f = mem_alloc_obj_zero(INIFileA_t);

	if (!f)
		return NULL;

	f->strm = stream;
	f->cmnt_chars = NULL;
	return f;
}
PINIFileW_t ini_neww(FILE* stream)
{
	if (!stream)
		return NULL;

	INIFileW_t* f = mem_alloc_obj_zero(INIFileW_t);

	if (!f)
		return NULL;

	f->strm = stream;
	f->cmnt_chars = NULL;
	return f;
}

#define ini_new_filea(file) ini_newa(file_opena(file, "r"))
#define ini_new_filew(file) ini_neww(file_openw(file, L"r"))

#define ini_comment_chars(pInifile) pInifile->cmnt_chars 
//#define ini_comment_charsw(pInifilew) ini_comment_chars(pInifilew)

#define ini_stream(pInifilew) pInifilew->strm


bool ini_closea(PINIFileA_t file)
{
	if (file && file_close(file->strm) == 0)
	{
		file->strm = NULL;
		//cleanup

		if (file->buff_line)
		{
			mem_free(file->buff_line);
			file->buff_line = NULL;
		}
		mem_free(file);
		file = NULL;
		return true;
	}
	return false;
}
bool ini_closew(PINIFileW_t file)
{
	if (file && file_close(file->strm) == 0)
	{
		file->strm = NULL;
		//cleanup

		if (file->buff_line)
		{
			mem_free(file->buff_line);
			file->buff_line = NULL;
		}
		mem_free(file);
		file = NULL;
		return true;
	}
	return false;
}

bool ini_readlinea(PINIFileA_t file)
{
	if (file->buff_line)
	{
		mem_free(file->buff_line);
		file->buff_line = NULL;
	}
	file->buff_line = file_readlinea(file->strm);
	return file->buff_line;
}
bool ini_readlinew(PINIFileW_t file)
{
	if (file->buff_line)
	{
		mem_free(file->buff_line);
		file->buff_line = NULL;
	}
	file->buff_line = file_readlinew(file->strm);
	return file->buff_line;
}

char* ___remove_commentsa(char* begin, char* end, const char* cmnt_chars)
{
	if (!cmnt_chars)
		return end;

	char* endpt_cc = str_find(begin, end, cmnt_chars, SF_NONE);
	if (endpt_cc)
	{
		*endpt_cc = '\0';
		return (begin == endpt_cc) ? begin : --endpt_cc;
	}

	return end;
}
wchar_t* ___remove_commentsw(wchar_t* begin, wchar_t* end, const wchar_t* cmnt_chars)
{
	if (!cmnt_chars)
		return end;

	wchar_t* endpt_cc = strw_find(begin, end, cmnt_chars, SF_NONE);
	if (endpt_cc)
	{
		*endpt_cc = L'\0';
		return (begin == endpt_cc) ? begin : --endpt_cc;
	}

	return end;
}

void ___remove_whitespacesa(char** begin, char** end)
{
	*begin = str_find(*begin, *end, " ", SF_NOT);
	if (*begin)
		*end = str_find(*begin, *end, " ", SF_NOT | SF_REVERSE);


}
void ___remove_whitespacesw(wchar_t** begin, wchar_t** end)
{
	*begin = strw_find(*begin, *end, L" ", SF_NOT);
	if (*begin) 
		*end = strw_find(*begin, *end, L" ", SF_NOT | SF_REVERSE);
}

bool ini_parselinea(PINIFileA_t file, PINIParseLineResultA_t result)
{
	if (!file->buff_line)
		return false;


	char* begin = file->buff_line;
	char* end = str_end(begin);

	if (begin && end && begin != end)
	{
		//remove comments
		end = ___remove_commentsa(begin, end, file->cmnt_chars);// remove comments at the end... if any

		//remove whitespaces
		___remove_whitespacesa(&begin, &end);// remove whitespaces front & back

		if (begin == NULL || end == NULL)
			return false;


		mem_zero(result, sizeof(PINIParseLineResultA_t));

		if (*begin == '[')
		{
			result->pSection = begin;
			return true;
		}

		char* equpt = str_find(begin, end, "=", SF_NONE);
		if (equpt)
		{
			*equpt = '\0';

			result->pKey = begin;
			result->pValue = ++equpt;
			return true;
		}
	}
	return false;
}
bool ini_parselinew(PINIFileW_t file, PINIParseLineResultW_t result)
{
	if (!file->buff_line)
		return false;


	wchar_t* begin = file->buff_line;
	wchar_t* end = strw_end(begin);

	if (begin && end && begin != end)
	{
		//remove comments
		end = ___remove_commentsw(begin, end, file->cmnt_chars);// remove comments at the end... if any

		//remove whitespaces
		___remove_whitespacesw(&begin, &end);// remove whitespaces front & back

		if (begin == NULL || end == NULL)
			return false;


		mem_zero(result, sizeof(PINIParseLineResultW_t));

		if (*begin == L'[')
		{
			result->pSection = begin;
			return true;
		}
		wchar_t* equpt = strw_find(begin, end, L"=", SF_NONE);
		if (equpt)
		{
			*equpt = L'\0';

			result->pKey = begin;
			result->pValue = ++equpt;
			return true;
		}
	}
	return false;
}






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