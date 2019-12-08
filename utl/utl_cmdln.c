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

			//pParser->buff_len = 0;
			//pParser->buffer = NULL;

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

			//pParser->buff_len = 0;
			//pParser->buffer = NULL;

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
		int ncur = str_len(cur);

		for (int i = 0; i < pParser->sargc; i++)
		{
			pParser->result.kidx = i;
			pParser->result.key = pParser->sargv[i];
			int nscur = str_len(pParser->result.key);

			if (ncur >= nscur)
			{
				if (CMDLN_STR_CMPN(cur, pParser->result.key, nscur) == 0)
				{
					if (ncur == nscur)//form --> <arg1> <arg2>
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
						pParser->result.val = (cur + nscur);
						if (*pParser->result.val == '=' || *pParser->result.val == ':')
						{
							++pParser->result.val;
							return cmdln_parser_get_result(pParser);
						}
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
		int ncur = strw_len(cur);


		for (int i = 0; i < pParser->sargc; i++)
		{
			pParser->result.kidx = i;
			pParser->result.key = pParser->sargv[i];
			int nscur = strw_len(pParser->result.key);

			if (ncur >= nscur)
			{
				if (CMDLN_STRW_CMPN(cur, pParser->result.key, nscur) == 0)
				{
					if (ncur == nscur)//form --> <arg1> <arg2>
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
						pParser->result.val = (cur + nscur);
						if (*pParser->result.val == L'=' || *pParser->result.val == L':')
						{
							++pParser->result.val;
							return cmdln_parser_get_result(pParser);
						}
					}
				}
			}
		}
	}
	return NULL;
}