#include"leptjson.h"
#include<assert.h>
#include<stdlib.h>
//移动一下指针
#define EXPECT(c, ch) do{assert(*c->json == (ch)); ++c->json;} while(0)

struct lept_context{
	const char* json;
};
//跳过空格
static void lept_parse_whitespace(lept_context* c) {
	const char *p = c->json;
	while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t') {
		++p;
	}
	c->json = p;
}
//null
static int lept_parse_null(lept_context* c, lept_value* v) {
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = LEPT_NULL;
	return LEPT_PARSE_OK;
}	
//true
static int lept_parse_true(lept_context* c, lept_value* v) {
	EXPECT(c, 't');
	if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = LEPT_TRUE;
	return LEPT_PARSE_OK;
}
//false
static int lept_parse_false(lept_context* c, lept_value* v) {
	EXPECT(c, 'f');
	if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 4;
	v->type = LEPT_FALSE;
	return LEPT_PARSE_OK;
}
//判断数据类型
static int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json){
	case 't': return lept_parse_true(c, v);
	case 'f': return lept_parse_false(c, v);
	case 'n': return lept_parse_null(c, v);
	case '\0': return LEPT_PARSE_EXPECT_VALUE;
	}
}
//获取json类型
int lept_parse(lept_value* v, const char* json) {
	lept_context t;
	assert(v != nullptr);
	v->type = LEPT_NULL;
	t.json = json;
	lept_parse_whitespace(&t);
	int ret;
	if ((ret = lept_parse_value(&t, v)) == LEPT_PARSE_OK){
		lept_parse_whitespace(&t);
		if (*t.json != '\0') {
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
			v->type = LEPT_NULL;
		}
	}
	return ret;
}
//返回json类型
lept_type lept_get_type(const lept_value *v) {
	assert(v != nullptr);
	return v->type;
}

