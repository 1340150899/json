#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include"leptjson.h"
using namespace std;
static int test_count = 0;
static int test_pass = 0;
//用宏测试实际和预计的情况
#define EXPECT_EQ_BASE(equality, expect, actual, format)\
	do{\
		++test_count;\
		if(equality)\
			++test_pass;\
		else fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
	}while(0)
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%d")
#define EXPECT_EQ_NUMBER(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")
//测试宏
#define TEST_ALL(expect, json)\
	do{\
		lept_value v;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(expect, lept_get_type(&v));\
	}while(0)
//测试获取的数字
#define TEST_NUMBER(json)\
	do{\
		lept_value v;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(LEPT_NUMBER, lept_get_type(&v));\
		cout<< "get_number: "<<lept_get_number(&v)<< endl;\
	}while(0)

#define TEST_STRING(expect, json)\
    do {\
        lept_value v;\
        lept_init(&v);\
        EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(LEPT_STRING, lept_get_type(&v)); \
		EXPECT_EQ_STRING(expect, lept_get_string(&v), lept_get_string_length(&v)); \
        lept_free(&v);\
    } while(0)
			
static void test_parse_string() {
#if 0
	TEST_STRING("", "\"\"");
	TEST_STRING("Hello", "\"Hello\"");
	TEST_STRING("Hello World", "\"Hello World\"");
#endif
#if 1
	TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
	TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
#endif
}
 
void test_parse() {
	////null
	//TEST_ALL(LEPT_NULL, "null");
	////true
	//TEST_ALL(LEPT_TRUE, "true");
	////false
	//TEST_ALL(LEPT_FALSE, "false");
	////number
	//TEST_ALL(LEPT_NUMBER, "123");
	////get_number
	//TEST_NUMBER("1e10");
	//string
	test_parse_string();
	////测试错误情况
	//TEST_ALL(LEPT_NULL, "null n");
	cout << test_pass << " " << test_count << " " 
	<< "passed:" << test_pass * 100.0 / test_count << "%"<< endl;

}