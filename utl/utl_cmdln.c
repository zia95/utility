#include "utl_cmdln.h"


PCmdLnParserA_t cmdln_parser_newa(int argc, char** argv, int sargc, const char** sargv)
{
	if (argc > 0 || argv != NULL || sargc > 0 || sargv != NULL)
	{
		PCmdLnParserA_t pParser = (PCmdLnParserA_t)malloc(sizeof(CmdLnParserA_t));
		if (pParser)
		{
			pParser->argc = argc;
			pParser->argv = argv;
			pParser->sargc = sargc;
			pParser->sargv = sargv;

			pParser->argc_idx = 0;

			pParser->buff_len = 0;
			pParser->buffer = NULL;

			memset(&pParser->result, 0, sizeof(pParser->result));

			return pParser;
		}
	}
	return NULL;
}
PCmdLnParserW_t cmdln_parser_neww(int argc, wchar_t** argv, int sargc, const wchar_t** sargv)
{
	if (argc > 0 || argv != NULL || sargc > 0 || sargv != NULL)
	{
		PCmdLnParserW_t pParser = (PCmdLnParserW_t)malloc(sizeof(CmdLnParserW_t));
		if (pParser)
		{
			pParser->argc = argc;
			pParser->argv = argv;
			pParser->sargc = sargc;
			pParser->sargv = sargv;

			pParser->argc_idx = 0;

			pParser->buff_len = 0;
			pParser->buffer = NULL;

			memset(&pParser->result, 0, sizeof(pParser->result));

			return pParser;
		}
	}
	return NULL;
}

PKeypairA_t cmdln_parsea(PCmdLnParserA_t pParser)
{
	memset(&pParser->result, 0, sizeof(pParser->result));

	if (pParser->argc_idx < pParser->argc)
	{
		char* cur = pParser->argv[pParser->argc_idx];


		for (int i = 0; i < pParser->sargc; i++)
		{
			const char* scur = pParser->sargv[i];
			if (str_cmpi(cur, scur) == 0)
			{
				pParser->result.key = cur;
				if (++pParser->argc_idx < pParser->argc)
				{
					pParser->result.val = pParser->argv[pParser->argc_idx];
					--pParser->argc_idx;
				}

				return cmdln_parser_get_result(pParser);
			}
			else
			{
				char* sep = str_find(cur, str_end(cur), ":=", SF_NONE);

				if (sep)
				{
					size_t scur_len = str_len(scur);
					if (str_cmpn(cur, scur, scur_len) == 0)
					{
						//buffer must be created because 'argv' memory is write protected (i.e. read-only). 
						if (pParser->buffer)
						{
							str_free(pParser->buffer);
							pParser->buffer = NULL;
						}

						pParser->buff_len = str_len(cur);
						pParser->buffer = str_new_zero(pParser->buff_len + 1); //(char*)calloc(pParser->buff_len + 1, sizeof(char));

						str_cpy(pParser->buffer, cur);

						char* bsep = (pParser->buffer + scur_len);

						*bsep = '\0';

						pParser->result.key = pParser->buffer;
						pParser->result.val = ++bsep;
						return cmdln_parser_get_result(pParser);
					}
				}
			}
		}
	}
	return NULL;
}
PKeypairW_t cmdln_parsew(PCmdLnParserW_t pParser)
{
	memset(&pParser->result, 0, sizeof(pParser->result));

	if (pParser->argc_idx < pParser->argc)
	{
		wchar_t* cur = pParser->argv[pParser->argc_idx];


		for (int i = 0; i < pParser->sargc; i++)
		{
			const wchar_t* scur = pParser->sargv[i];
			if (strw_cmpi(cur, scur) == 0)//form --> <arg1> <arg2>
			{
				pParser->result.key = cur;
				if (++pParser->argc_idx < pParser->argc)
				{
					pParser->result.val = pParser->argv[pParser->argc_idx];
					--pParser->argc_idx;
				}

				return cmdln_parser_get_result(pParser);
			}
			else//form --> <arg1> where <arg1> --> key:val OR key=val
			{
				wchar_t* sep = strw_find(cur, strw_end(cur), L":=", SF_NONE);

				if (sep)
				{
					int scur_len = strw_len(scur);
					if (strw_cmpn(cur, scur, scur_len) == 0)
					{
						//buffer must be created because 'argv' memory is write protected (i.e. read-only). 
						if (pParser->buffer)
						{
							free(pParser->buffer);
							pParser->buffer = NULL;
						}

						pParser->buff_len = strw_len(cur);
						pParser->buffer = strw_new_zero(pParser->buff_len + 1);// (wchar_t*)calloc(pParser->buff_len + 1, sizeof(wchar_t));


						strw_cpy(pParser->buffer, cur);

						wchar_t* bsep = (pParser->buffer + scur_len);

						*bsep = L'\0';

						pParser->result.key = pParser->buffer;
						pParser->result.val = ++bsep;
						return cmdln_parser_get_result(pParser);
					}
				}
			}
		}
	}
	return NULL;
}