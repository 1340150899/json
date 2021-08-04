#pragma once
#ifndef LEPTJSON_ H__
#define LEPTJSON_ H__

enum lept_type
{
	LEPT_NULL,LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER,
	LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
};

struct lept_value {
	lept_type type;
};

enum
{
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value *v);

void test_parse();
#endif // !LEPTJSON_ H__
