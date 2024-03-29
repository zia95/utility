#ifndef UTL_FILE
#define UTL_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utl_mem.h"
#include <wchar.h>
#include "utl_str.h"
#include "utl_env.h"


#pragma warning(disable:4996)//unsafe warn


#define FILE_NAME_MAX FILENAME_MAX
#define FILE_TEMP_NAME_MIN L_tmpnam


#define file_removea(filename) remove(filename)
#define file_renamea(filename_old, filename_new) rename(filename_old, filename_new)
#define file_gentmp() tmpfile()
#define file_gentmpnamea(filename) tmpnam (filename)


#define file_getsa(buffer, count, stream) fgets(buffer, count, stream)
#define file_getsw(buffer, count, stream) fgetws(buffer, count, stream)


#define file_opena(file, mode) fopen(file, mode)
#if _WIN32 || _WIN64
#define file_openw(file, mode) _wfopen(file, mode)
#else
FILE* file_openw(const wchar_t* file, const wchar_t* mode);
#endif

#define file_close(file) fclose(file)

__inline bool file_exista(const char* file)
{
	FILE* f = file_opena(file, "r");
	if (f)
		return file_close(f) == 0;
	return false;
}
__inline bool file_existw(const wchar_t* file)
{
	FILE* f = file_openw(file, L"r");
	if (f)
		return file_close(f) == 0;
	return false;
}





#define file_clear_streama(stream)	{ int c;	while ((c = fgetc(stream))		!= '\n' && c != EOF){} }
#define file_clear_streamw(wstream) { wint_t c; while ((c = fgetwc(wstream))	!= L'\n' && c != WEOF){} }


__inline long file_get_size(FILE* f)
{
	if (f)
	{
		if (fseek(f, -1, SEEK_END) == 0)
		{
			long file_len = ftell(f);
			if (fseek(f, 0, SEEK_SET) == 0)
			{
				return file_len;
			}
		}
	}
	return -1;
}

__inline bool file_writetexta(const char* file, const char* txt, bool append)
{
	FILE* f = file_opena(file, append ? "a" : "w");
	if (f)
	{
		fprintf(f, "%s", txt);
		return (file_close(f) == 0);
	}
	return false;
}

__inline bool file_writetextw(const wchar_t* file, const wchar_t* txt, bool append)
{
	FILE* f = file_openw(file, append ? L"a" : L"w");
	if (f)
	{
		fwprintf(f, L"%s", txt);
		return (file_close(f) == 0);
	}
	return false;
}


long file_reada(FILE* _stream, char* buf, long len);
long file_readw(FILE* _stream, wchar_t* buf, long len);

char* file_readlinea(FILE* _stream);
wchar_t* file_readlinew(FILE* _stream);

char* file_readalla(FILE* _stream, long* pflen);
wchar_t* file_readallw(FILE* _stream, long* pflen);


#endif // !UTL_FILE
