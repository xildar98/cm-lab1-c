//
// Created by cubazis on 27.08.18.
//
#include <check.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "parcer.h"

FILE *fmemopen (void *bf, size_t size, const char *mode);

char* contains_error(char* s){
    char error[] = "ERROR";
    if (strstr(s,error )==0 ){
        return "0";
    } else{
        return "1";
    }
}

/***************************************************************************************************/
/****************************       lexical analyzer test cases      *******************************/
/***************************************************************************************************/

/** DEMO TEST: Demonstrate how to test my lex() code in a test suite by using FILE stream */
START_TEST (test_lex_0)
{
	char* input = "";
	char* pattern = 0;
	file = fmemopen(input, strlen(input), "r");

	int res = (int)lex();

	printf("%d\n", res);
	ck_assert_int_eq(res, pattern);
}
END_TEST

START_TEST (test_lex_1)
    {
        char* input = "135";
        char* pattern = 6;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_2)
    {
        char* input = "00257";
        char* pattern = 6;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_3)
    {
        char* input = "+";
        char* pattern = 2;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_4)
    {
        char* input = "*";
        char* pattern = 3;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_5)
    {
        char* input = "(";
        char* pattern = 4;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_6)
    {
        char* input = ")";
        char* pattern = 5;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

START_TEST (test_lex_7)
    {
        char* input = ";";
        char* pattern = 1;
        file = fmemopen(input, strlen(input), "r");

        int res = (int)lex();

        printf("%d\n", res);
        ck_assert_int_eq(res, pattern);
    }
END_TEST

/** YOUR TESTS HERE */


/***************************************************************************************************/
/****************************            parser test cases           *******************************/
/***************************************************************************************************/

/** DEMO TEST: Demonstrate how to test your code in a test suite by using FILE stream */
START_TEST (test_parser_with_file_input)
{
	/** be careful: file - is a parser internal entity */
	file = fopen( "../../in.txt" , "r");

	char* pattern = "NUM SEMI EOF";

	statements();

	printf("%s\n", parser_result);
	ck_assert_str_eq(parser_result, pattern);

	/** Don't forget to close it */
	fclose(file);
}
END_TEST

/** DEMO TEST: Demonstrate how to test your code in a test suite by using char* stream
 *  here I've used fmemopen function to wrap up the char* stream by FILE descriptor
 *  otherwise I would be forced to

 */

START_TEST (test_parser_0)
{
	char* input = ";";
	char* pattern = "SEMI EOF"; //update, because initial test was incorrect. By BNF expression cant be empty
	file = fmemopen(input, strlen(input), "r");
	statements();
	printf("%s\n", parser_result);
	ck_assert_str_eq(contains_error(parser_result), "1");
	fclose(file);
}
END_TEST

START_TEST (test_parser_1)
{
	char* input = "1+2;";
	char* pattern = "NUM PLUS NUM SEMI EOF";
	file = fmemopen(input, strlen(input), "r");
	statements();
	printf("%s\n", parser_result);
	ck_assert_str_eq(parser_result, pattern);
	fclose(file);

}
END_TEST

START_TEST (test_parser_2)
{
	char* input = "1+2; 1+2*3+2;\n1+3;";
	char* pattern = "NUM PLUS NUM SEMI NUM PLUS NUM TIMES NUM PLUS NUM SEMI NUM PLUS NUM SEMI EOF";
	file = fmemopen(input, strlen(input), "r");
	statements();
	printf("%s\n", parser_result);
	ck_assert_str_eq(parser_result, pattern);
	fclose(file);
}
END_TEST

START_TEST (test_parser_3)
    {
        char* input = "1+3++;";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(contains_error(parser_result), "1");
        fclose(file);
    }
END_TEST

START_TEST (test_parser_4)
    {
        char* input = "1+3;";
        char* pattern = "NUM PLUS NUM SEMI EOF";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(parser_result, pattern);
        fclose(file);
    }
END_TEST

START_TEST (test_parser_5)
    {
        char* input = "1+;";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(contains_error(parser_result), "1");
        fclose(file);
    }
END_TEST

START_TEST (test_parser_6)
    {
        char* input = "";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(contains_error(parser_result), "1");
        fclose(file);
    }
END_TEST

START_TEST (test_parser_7)
    {
        char* input = "(2+3)+(1+2);";
        char* pattern = "LP NUM PLUS NUM RP PLUS LP NUM PLUS NUM RP SEMI EOF";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(parser_result, pattern);
        fclose(file);
    }
END_TEST

START_TEST (test_parser_8)
    {
        char* input = "(2+3)+(1+2);2+2;";
        char* pattern = "LP NUM PLUS NUM RP PLUS LP NUM PLUS NUM RP SEMI NUM PLUS NUM SEMI EOF";
        file = fmemopen(input, strlen(input), "r");
        statements();
        printf("%s\n", parser_result);
        ck_assert_str_eq(parser_result, pattern);
        fclose(file);
    }
END_TEST


/***************************************************************************************************/
/****************************          service do not touch          *******************************/
/***************************************************************************************************/

/** SERVICE FUNCTION
 * fmemopen function emulates FILE descriptor for stream of bytes, in our case is a char* string
 * this function is in GNU C Compiler only. That's why I added this emulation code here
 * if you use GNU C Compiler - you don't need this implementation
 * @param bf stream buffer
 * @param size size of chunk
 * @param mode file open mode
 * @return FILE descriptor
 */

/*
FILE *fmemopen (void *bf, size_t size, const char *mode)
{
	FILE *f;
	assert(strcmp(mode, "r") == 0);
	f = tmpfile();
	fwrite(bf, 1, size, f);
	rewind(f);
	return f;
}
*/
/***************************************************************************************************/
/****************************           add test cases only          *******************************/
/***************************************************************************************************/

Suite* str_suite (void)
{
	Suite *suite = suite_create("parser");
	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test_parser_with_file_input);


	tcase_add_test(tcase, test_lex_0);
    //my test
    tcase_add_test(tcase, test_lex_1);
    tcase_add_test(tcase, test_lex_2);
    tcase_add_test(tcase, test_lex_3);
    tcase_add_test(tcase, test_lex_4);
    tcase_add_test(tcase, test_lex_5);
    tcase_add_test(tcase, test_lex_6);
    tcase_add_test(tcase, test_lex_7);

	tcase_add_test(tcase, test_parser_0);
	tcase_add_test(tcase, test_parser_1);
	tcase_add_test(tcase, test_parser_2);

    //my test
    tcase_add_test(tcase, test_parser_3);
    tcase_add_test(tcase, test_parser_4);
    tcase_add_test(tcase, test_parser_5);
    tcase_add_test(tcase, test_parser_6);
    tcase_add_test(tcase, test_parser_7);

	suite_add_tcase(suite, tcase);
	return suite;
}

int main (int argc, char *argv[]) {
	int number_failed;
	Suite *suite = str_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}