#include <stdio.h>
#include <errno.h>


#include "utl.h"
#include "utl_file.h"
#include "utl_str.h"
#include "utl_str_type.h"
#include "utl_locale.h"

#include "utl_llist.h"
#include "utl_ini.h"

int read_allw(FILE* stream)
{
	wint_t wc;
	errno = 0;
   while (WEOF != (wc = fgetwc(stream)))
      printf("%lc", wc);

	printf("\n");
   if (EILSEQ == errno) {
      printf("An invalid wide character was encountered.\n");
      exit(1);
   }
   fclose(stream);
   return 0;
}
int ex_read_w(void)
{
   FILE   *stream;


   if (NULL == (stream = file_openw(L"/home/ziauddin/Projects/test_inp.txt", L"r")))
   {
      printf("Unable to open: \"fgetwc.dat\"\n");
      exit(1);
   }
   return read_allw(stream);
}




void test_wfile()
{
	FILE* f = file_openw(L"/home/ziauddin/Projects/test_inp.txt", L"r");

	if (f)
	{
		//read_allw(f);

		//wchar_t * c = strw_new_zero(1000);
		//file_readw(f, c, 1000);
		//wprintf(L"%ls\n", c);


		long len;
		wchar_t* fd = file_readallw(f, &len);
		if (fd)
		{
			wprintf(L"%ls\n", fd);
			mem_free(fd);
		}

		file_close(f);
	}
	else
	{
		wprintf(L"ERROR: Failed to open file.");
	}

}
void test_file()
{
	FILE* f = file_opena("/home/ziauddin/Projects/test_inp.txt", "r");

	if (f)
	{
		long len;
		char* fd = file_readalla(f, &len);
		if (fd)
		{
			printf("%s\n", fd);

			mem_free(fd);
		}
		file_close(f);
	}
	else
	{
		perror("ERROR: Failed to open file.");
	}

}

void test_wstring_conv()
{
	wchar_t* f = L"C:/Users/ziaud/Desktop/test/str.txt";
	char* fa = NULL;
	if(strw_tombs(&fa, f))
	{
		printf("%s\n", fa);
		str_free(fa);
	}
}
void test_string_conv()
{
	char* f = "C:/Users/ziaud/Desktop/test/str.txt";
	wchar_t* fw = NULL;
	if(str_towcs(&fw, f))
	{
		wprintf(L"%ls\n", fw);
		strw_free(fw);
	}
}


void test_str()
{
	/*
	pcstr m = "My name is Ziauddin.";
	pstr res = str_find(m, str_end(m), "My name is ", SF_MATCH_AS_WHOLE | SF_NOT | SF_REVERSE);
	if (res)
	{
		printf("Matched! (res:%s)\n", res);
	}
	*/

	printf("sizeof(int):sizeof(long) --> %d:%d\n", sizeof(int), sizeof(long));


	printf("str_todouble(): %f\n", str_todouble("50.499926"));
	printf("str_tofloat(): %f\n", str_tofloat("240.499926"));
	printf("str_tolong(): %d\n", str_tolong("854", 10));
	printf("str_tollong(): %d\n", str_tollong("4462", 10));
	printf("str_toulong(): %d\n", str_toulong("-265", 10));
	printf("str_toullong(): %d\n", str_toullong("12415", 10));
}
void test_strw()
{
	pcstrw m = L"My name is Ziauddin.";
	pcstrw res = strw_find(m, strw_end(m), L"My name is ", SF_MATCH_AS_WHOLE | SF_NOT | SF_REVERSE);
	if (res)
	{
		wprintf(L"Matched! (res:%ls)\n", res);
	}
}

void test_str_remove()
{
	char mystr[] = "my name is ziauddin.";
	pstr rm = str_remove(mystr, str_end(mystr), L'd');
	printf("new_str: '%s'\n", mystr);
}
void test_strw_remove()
{
	wchar_t mystr[] = L"my name is ziauddin.";
	pstr rm = strw_remove(mystr, strw_end(mystr), L'd');
	printf("new_str: '%ls'\n", mystr);
}

void test_str_remove2()
{
	char mystr[] = "my name is ziauddin.";

	char* sub_bgn = mystr + 11;
	pstr rm = str_remove_range(mystr, str_end(mystr), sub_bgn, (sub_bgn+3));
	*rm = '\0';
	printf("new_str: '%s'\n", mystr);
}
void test_strw_remove2()
{
	wchar_t mystr[] = L"my name is ziauddin.";

	wchar_t* sub_bgn = mystr + 11;
	pstrw rm = strw_remove_range(mystr, strw_end(mystr), sub_bgn, (sub_bgn + 3));
	*rm = L'\0';
	printf("new_str: '%ls'\n", mystr);
}

void  __llist_iter_cb(PLList pl, size_t idx, PLLElement pelm)
{
	printf("[%d] [%s]\n", idx, pelm->pdata);
}

void test_llist()
{
	PLList pl = llist_new();

	llist_add_range(pl, 5, "elm1", "elm2", "elm3", "elm4", "elm5");

	printf("before\n");
	llist_iter(pl, __llist_iter_cb);


	llist_remove(pl, 0);
	llist_remove(pl, 3);

	printf("after remove\n");
	llist_iter(pl, __llist_iter_cb);

	llist_add(pl, "zia1");
	llist_add(pl, "zia2");
	
	llist_remove_elm(pl, llist_add(pl, "zia3"));

	PLLElement e = llist_add(pl, "ziaXX");
	llist_add(pl, "ziaXX2");
	llist_add(pl, "ziaXX2YY");

	llist_remove_elm(pl, e);

	printf("after remove 2 and adding 6\n");
	llist_iter(pl, __llist_iter_cb);

	llist_free(pl);

}




//C:\Users\ziaud\Desktop\test\test.ini
#define INI_FILE "C:/Users/ziaud/Desktop/test/test.ini"
#define INI_FILEW L"C:/Users/ziaud/Desktop/test/test.ini"

int test_iniw()
{
	wprintf(L"\n====>RUNNING INI TEST <wchar_t:%d>\n", sizeof(wchar_t));
	PINIFileW_t file = ini_new_filew(INI_FILEW);
	ini_comment_chars(file) = DEF_CMNT_CHARW;
	if (file)
	{
		while (ini_readlinew(file))
		{
			INIParseLineResultW_t res;
			if (ini_parselinew(file, &res))
			{
				if (res.pSection)
				{
					wprintf(L"%s\n", res.pSection);

				}
				else
				{
					wprintf(L"%s=%s\n", res.pKey, res.pValue);
				}
			}
			else
			{

			}
		}
		ini_closew(file);
	}
}
int test_ini()
{
	printf("\n====>RUNNING INI TEST <char:%d>\n", sizeof(char));
	PINIFileA_t file = ini_new_filea(INI_FILE);
	ini_comment_chars(file) = DEF_CMNT_CHAR;
	if (file)
	{
		while (ini_readlinea(file))
		{
			INIParseLineResultA_t res;
			if (ini_parselinea(file, &res))
			{
				if (res.pSection)
				{
					printf("%s\n", res.pSection);

				}
				else
				{
					printf("%s=%s\n", res.pKey, res.pValue);
				}
			}
			else
			{

			}
		}
		ini_closea(file);
	}
}



/*
void cmdln_testa()
{
	printf(L"\n====>RUNNING TEST <char:%d>\n", sizeof(char));

	char* __myargv[6] = { "name", "zia", "age:22", "afweg", "gender:male", "agegf333" };
	char* __mysargv[3] = { "name", "age", "gender" };

	PCmdLnParserA_t parser = cmdln_parser_newa(6, __myargv, 3, __mysargv);

	if (parser)
	{
		printf("------------------------------\n");

		cmdln_first(parser);

		do
		{
			PKeypairA_t res = cmdln_parsea(parser);
			if (res)
			{
				printf("key:%s\nval:%s\n", res->key, res->val);
				printf("------------------------------\n");
			}
		} while (cmdln_next(parser));

		cmdln_parser_free(parser);
	}
}
void cmdln_testw()
{
	wprintf(L"\n====>RUNNING TEST <wchar_t:%d>\n", sizeof(wchar_t));

	wchar_t* __myargv[6] = { L"--name", L"zia", L"--age:22", L"afweg", L"--gender=male", L"agegf333" };
	wchar_t* __mysargv[3] = { L"--name", L"--age", L"--gender" };

	PCmdLnParserW_t parser = cmdln_parser_neww(6, __myargv, 3, __mysargv);


	if (parser)
	{
		wprintf(L"------------------------------\n");

		cmdln_first(parser);

		do
		{
			PKeypairW_t res = cmdln_parsew(parser);
			if (res)
			{
				wprintf(L"key:%ls\nval:%ls\n", res->key, res->val);
				wprintf(L"------------------------------\n");
			}
		} while (cmdln_next(parser));

		cmdln_parser_free(parser);
	}
}
int cmdln_test()
{

	cmdln_testa();
	cmdln_testw();
}
*/








int main()
{

	test_str_remove();
	test_strw_remove();
	test_str_remove2();
	test_strw_remove2();

	//test_ini();
	//test_iniw();
	//test_llist();





	//test_str();







	//const char* info = locale_set_default();
	//ex_read_w();
	//test_wfile();
	//test_file();

	//test_string_conv();

	//printf("%d:%d\n", sizeof(char), sizeof(wchar_t));
}