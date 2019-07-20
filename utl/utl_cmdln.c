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
			pParser->result.kidx = i;
			pParser->result.key = pParser->sargv[i];

			if (CMDLN_STR_CMP(cur, pParser->result.key) == 0)
			{
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
					size_t scur_len = str_len(pParser->result.key);
					if (CMDLN_STR_CMPN(cur, pParser->result.key, scur_len) == 0)
					{
						//buffer must be created because 'argv' memory is write protected (i.e. read-only).

						// checking buffer len ---- memory clear ---- mem reloc --- it will increase performance. maybe?? 
						// nonetheless lets just go with free() and alloc()
						if (pParser->buffer)
						{
							str_free(pParser->buffer);
							pParser->buffer = NULL;
						}


						cur = (cur + scur_len + 1);// adding '+1' for seprator
						pParser->buff_len = str_len(cur);

						if (pParser->buff_len <= 0)
							return NULL;

						pParser->buffer = str_dup(cur, pParser->buff_len);

						pParser->result.val = pParser->buffer;
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
			pParser->result.kidx = i;
			pParser->result.key = pParser->sargv[i];
			if (CMDLN_STRW_CMP(cur, pParser->result.key) == 0)//form --> <arg1> <arg2>
			{
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
					int scur_len = strw_len(pParser->result.key);
					if (CMDLN_STRW_CMPN(cur, pParser->result.key, scur_len) == 0)
					{
						//buffer must be created because 'argv' memory is write protected (i.e. read-only). 
						// checking buffer len ---- memory clear ---- mem reloc --- it will increase performance. maybe??
						// nonetheless lets just go with free() and alloc()
						if (pParser->buffer)
						{
							strw_free(pParser->buffer);
							pParser->buffer = NULL;
						}

						cur = (cur + scur_len + 1);// adding '+1' for seprator
						pParser->buff_len = strw_len(cur);

						if (pParser->buff_len <= 0)
							return NULL;


						pParser->buffer = strw_dup(cur, pParser->buff_len);

						pParser->result.val = pParser->buffer;
						return cmdln_parser_get_result(pParser);
					}
				}
			}
		}
	}
	return NULL;
}