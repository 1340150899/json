#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include"leptjson.h"
using namespace std;
static int test_count = 0;
static int test_pass = 0;
//�ú����ʵ�ʺ�Ԥ�Ƶ����
#define EXPECT_EQ_BASE(equality, expect, actual, format)\
	do{\
		++test_count;\
		if(equality)\
			++test_pass;\
		else fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
	}while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%d")

#define EXPECT_EQ_NUMBER(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%.17g")

#define EXPECT_EQ_STRING(expect, actual, alength) EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && \
        memcmp(expect, actual, alength) == 0, expect, actual, "%s")

#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")

#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

//���Ժ�
#define TEST_ALL(expect, json)\
	do{\
		lept_value v;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(expect, lept_get_type(&v));\
	}while(0)
//���Ի�ȡ������
#define TEST_NUMBER(expect, json)\
    do {\
        lept_value v;\
        lept_init(&v);\
        EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
        EXPECT_EQ_INT(LEPT_NUMBER, lept_get_type(&v));\
        EXPECT_EQ_NUMBER(expect, lept_get_number(&v));\
        lept_free(&v);\
    } while(0)
static void test_parse_number() {
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");
	TEST_NUMBER(0.0, "-0.0");
	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");
	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");
	TEST_NUMBER(3.1416, "3.1416");
	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");
	TEST_NUMBER(-1E10, "-1E10");
	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1E+10, "-1E+10");
	TEST_NUMBER(-1E-10, "-1E-10");
	TEST_NUMBER(1.234E+10, "1.234E+10");
	TEST_NUMBER(1.234E-10, "1.234E-10");

	// ά���ٿ�˫���ȸ����� ��һЩ�߽�ֵ
	TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
	TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
	TEST_NUMBER(4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
	TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	TEST_NUMBER(2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
	TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	TEST_NUMBER(2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
	TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	TEST_NUMBER(1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
	TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}
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
	TEST_STRING("Hello", "\"Hello\"");
	TEST_STRING("", "\"\"");
	TEST_STRING("Hello World", "\"Hello World\"");
#endif
#if 1
	TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
	TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
#endif
}

#define TEST_ERROR(error, json)\
    do {\
        lept_value v;\
        lept_init(&v);\
        v.type = LEPT_FALSE;\
        EXPECT_EQ_INT(error, lept_parse(&v, json));\
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));\
        lept_free(&v);\
    } while(0)

static void test_parse_invalid_value() {
	//���Դ�������
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+0");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "+1");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "INF");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "inf");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "NAN");
	TEST_ERROR(LEPT_PARSE_INVALID_VALUE, "nan");
}

//��ʹ��lept_parse����
//��ʹ��lept_parse����ʱ��Ҫ������lept_init��lept_set��ʼ��
static void test_access_string() {
	lept_value v;
	lept_init(&v);
	lept_set_string(&v, "", 0);
	EXPECT_EQ_STRING("", lept_get_string(&v), lept_get_string_length(&v));
	lept_set_string(&v, "Hello", 5);
	EXPECT_EQ_STRING("Hello", lept_get_string(&v), lept_get_string_length(&v));
	lept_free(&v);
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
	//test_parse_number();
	////string
	//test_parse_string();


	//���Դ������
	//TEST_ALL(LEPT_NULL, "null n");
	//test_parse_invalid_value();

	//��ʹ��parse����
	test_access_string(); 




	//������Խ��
	cout << test_pass << " " << test_count << " " 
	<< "passed:" << test_pass * 100.0 / test_count << "%"<< endl;

}