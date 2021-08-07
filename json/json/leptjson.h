#pragma once
#ifndef LEPTJSON_ H__
#define LEPTJSON_ H__

enum lept_type
{
	LEPT_NULL,LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER,
	LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
};

struct lept_value {
	union
	{
		struct{
			char *s;
			size_t len;	
		}s;
		double n;
	}u;
	lept_type type;
};

enum
{
	//一切正常
	LEPT_PARSE_OK = 0,
	//若一个 JSON 只含有空白，传回 LEPT_PARSE_EXPECT_VALUE。
	LEPT_PARSE_EXPECT_VALUE,
	//若值格式不对 不知道是什么，传回 LEPT_PARSE_INVALID_VALUE。
	LEPT_PARSE_INVALID_VALUE,
	//若一个值之后 在空白之后还有其他字符，传回 LEPT_PARSE_ROOT_NOT_SINGULAR。
	LEPT_PARSE_ROOT_NOT_SINGULAR,
	//超过数字的最大值
	LEPT_PARSE_NUMBER_TOO_BIG,
	//字符串中含有 \0
	LEPT_PARSE_MISS_QUOTATION_MARK,
	//无法识别转义符 \ 后面的字符
	LEPT_PARSE_INVALID_STRING_ESCAPE,
	//字符串中有不合法的字符
	LEPT_PARSE_INVALID_STRING_CHAR,
	//utf-8不合法
	LEPT_PARSE_INVALID_UNICODE_HEX,
	//
	LEPT_PARSE_INVALID_UNICODE_SURROGATE
};

#define lept_init(v){(v)->type = LEPT_NULL;} while(0)

int lept_parse(lept_value* v, const char* json);

void lept_free(lept_value* v);

lept_type lept_get_type(const lept_value *v);

void test_parse();

#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);
#endif // !LEPTJSON_ H__
