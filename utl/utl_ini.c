#include "utl_ini.h"



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

inline char* ___remove_commentsa(char* begin, char* end, const char* cmnt_chars)
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
inline wchar_t* ___remove_commentsw(wchar_t* begin, wchar_t* end, const wchar_t* cmnt_chars)
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

inline void ___remove_whitespacesa(char** begin, char** end)
{
	*begin = str_find(*begin, *end, " ", SF_NOT);
	if (*begin)
		* end = str_find(*begin, *end, " ", SF_NOT | SF_REVERSE);


}
inline void ___remove_whitespacesw(wchar_t** begin, wchar_t** end)
{
	*begin = strw_find(*begin, *end, L" ", SF_NOT);
	if (*begin)
		* end = strw_find(*begin, *end, L" ", SF_NOT | SF_REVERSE);
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