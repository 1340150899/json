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

//测试宏
#define TEST_ALL(expect, json)\
	do{\
		lept_value v;\
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json));\
		EXPECT_EQ_INT(expect, lept_get_type(&v));\
	}while(0)

void test_parse() {
	//null
	TEST_ALL(LEPT_NULL, "null");
	//true
	TEST_ALL(LEPT_TRUE, "true");
	//false
	TEST_ALL(LEPT_FALSE, "false");
	//测试错误情况
	TEST_ALL(LEPT_NULL, "null n");
	cout << test_pass << " " << test_count << " " 
	<< "passed:" << test_pass * 100.0 / test_count << "%"<< endl;
}