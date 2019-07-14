#include "utl_file.h"

#if _WIN32 || _WIN64
#define WIN
#endif



#ifndef WIN
FILE* file_openw(const wchar_t* file, const wchar_t* mode)
{
	char* __file = NULL;
	char* __mode = NULL;
	if (strw_tombs(&__file, file) && strw_tombs(&__mode, mode))
	{
		FILE* f = file_opena(__file, __mode);
		str_free(__file);
		str_free(__mode);
		return f;
	}
	return NULL;
}
#endif


long file_get_size(FILE* f)
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

bool file_writetexta(const char* file, const char* txt, bool append)
{
	FILE* f = file_opena(file, append ? "a" : "w");
	if (f)
	{
		fprintf(f, "%s", txt);
		return (file_close(f) == 0);
	}
	return false;
}

bool file_writetextw(const wchar_t* file, const wchar_t* txt, bool append)
{
	FILE* f = file_openw(file, append ? L"a" : L"w");
	if (f)
	{
		fwprintf(f, L"%s", txt);
		return (file_close(f) == 0);
	}
	return false;
}


long file_reada(FILE * _stream, char* buf, long len)
{
	int c;
	long read = 0;
	for (; read < len; read++)
	{
		c = fgetc(_stream);
		if (c == EOF)
			break;
		buf[read] = c;
	}
	return read;
}
long file_readw(FILE * _stream, wchar_t* buf, long len)
{
	wint_t wc;
	long read = 0;
	for (; read < len; read++)
	{
		if ((wc = fgetwc(_stream)) == WEOF)
			break;
		buf[read] = wc;
	}
	return read;
}

char* file_readlinea(FILE * _stream)
{
	size_t lenmax = 100, len = lenmax;
	char* line = (char*)mem_alloc(lenmax), * linep = line;

	int c;

	if (line == NULL)
		return NULL;

	for (;;)
	{
		c = fgetc(_stream);
		if (c == EOF)
			break;

		if (--len == 0)
		{
			len = lenmax;
			char* linen = (char*)mem_realloc(linep, lenmax *= 2);

			if (linen == NULL)
			{
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if ((*line++ = c) == '\n')
		{
			*(--line) = '\0';
			break;
		}
	}

	if (len == lenmax && c == EOF)//end of file
	{
		free(linep);
		return NULL;
	}

	*line = '\0';
	return linep;
}
wchar_t* file_readlinew(FILE * _stream)
{
	size_t lenmax = 100, len = lenmax;
	wchar_t* line = (wchar_t*)mem_alloc(lenmax * sizeof(wchar_t)), * linep = line;

	wint_t c;

	if (line == NULL)
		return NULL;

	for (;;)
	{
		c = fgetwc(_stream);
		if (c == WEOF)
			break;

		if (--len == 0)
		{
			len = lenmax;
			wchar_t* linen = (wchar_t*)mem_realloc(linep, (lenmax *= 2) * sizeof(wchar_t));

			if (linen == NULL)
			{
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if ((*line++ = c) == L'\n')
		{
			*(--line) = L'\0';
			break;
		}
	}
	if (len == lenmax && c == WEOF)//end of file
	{
		free(linep);
		return NULL;
	}

	*line = L'\0';
	return linep;
}

char* file_readalla(FILE * _stream, long* pflen)
{
	char* buf = NULL;
	long len = -1;
	if (_stream)
	{
		len = file_get_size(_stream);

		if (pflen)
			* pflen = len;

		if (len > 0)
		{
			buf = (char*)mem_alloc((size_t)(len));

			if (buf)
			{
				long x = file_reada(_stream, buf, len);
				buf[++x] = '\0';
			}
		}
	}
	return buf;
}
wchar_t* file_readallw(FILE * _stream, long* pflen)
{
	wchar_t* buf = NULL;
	long len = -1;
	if (_stream)
	{
		len = file_get_size(_stream);

		if (pflen)
			* pflen = len;

		if (len > 0)
		{
			buf = (wchar_t*)mem_alloc((size_t)((len) * sizeof(wchar_t)));

			if (buf)
			{
				long x = file_readw(_stream, buf, len);
				buf[++x] = L'\0';
			}
		}
	}
	return buf;
}