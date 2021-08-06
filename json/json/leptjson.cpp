#include"leptjson.h"
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#ifndef LEPT_PARSE_STACK_INIT_SIZE
#define LEPT_PARSE_STACK_INIT_SIZE  256
#endif // !LEPT_PARSE_STACK_INIT_SIZE


//移动一下指针
#define EXPECT(c, ch)      do{assert(*c->json == (ch)); ++c->json;} while(0)
#define ISDIGIT(ch)        ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)    ((ch) >= '1' &&  (ch) <= '9')
#define	PUTC(c, ch)		   do{*(char*)lept_context_push(c, sizeof(char)) = (ch);}while(0)
struct lept_context{
	const char* json;
	char* stack;
	rsize_t size, top;
};

static void* lept_context_push(lept_context* c, size_t size) {
	void* ret;
	assert(size > 0);
	if (c->top + size >= c->size) {
		if (c->size == 0)
			c->size = LEPT_PARSE_STACK_INIT_SIZE;
		while (c->top + size >= c->size)
			c->size += c->size >> 1;
		c->stack = (char*)realloc(c->stack, c->size);
	}
	ret = c->stack + c->top;
	c->top += size;
	return ret;
}

static void* lept_context_pop(lept_context* c, size_t size) {
	assert(c->top >= size);
	return c->stack + (c->top -= size);
}

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
//数字
static int lept_parse_number(lept_context* c, lept_value* v) {
	const char *p = c->json;
	//判断是否是json格式的数字
	if (*p == '-') ++p;
	if (*p == '0') ++p;
	else {
		if (!ISDIGIT1TO9(*p)) return LEPT_PARSE_INVALID_VALUE;
		for (++p; ISDIGIT(*p); ++p);
	}
	if (*p == '.') {
		++p;
		if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
		for (++p; ISDIGIT(*p); ++p);
	}
	if (*p == 'e' || *p == 'E') {
		++p;
		if (*p == '+' || *p == '-') ++p;
		if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;
		for (++p; ISDIGIT(*p); ++p);
	}
	errno = 0;
	v->u.n = strtod(c->json, nullptr);
	if (errno == ERANGE && (v->u.n == HUGE_VAL) || v->u.n == -HUGE_VAL) {
		return LEPT_PARSE_NUMBER_TOO_BIG;
	}
	v->type = LEPT_NUMBER;
	//如果是p应该走到了末尾
	c->json = p;
	return LEPT_PARSE_OK;
}

//string
static int lept_parse_string(lept_context* c, lept_value* v) {
	size_t head = c->top, len;
	const char* p;
	EXPECT(c, '\"');
	p = c->json;
	for (;;) {
		char ch = *p++;
		switch (ch){
		case '\"':
			len = c->top - head;
			lept_set_string(v, (const char*)lept_context_pop(c, len), len);
			c->json = p;
			return  LEPT_PARSE_OK;
		case '\0':
			c->top = head;
			return LEPT_PARSE_MISS_QUOTATION_MARK;
		default:
			PUTC(c, ch);			
		}
	}
}
//判断数据类型
static int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json){
	case 't':  return lept_parse_true(c, v);
	case 'f':  return lept_parse_false(c, v);
	case 'n':  return lept_parse_null(c, v);
	case '"':  return lept_parse_string(c, v);
	case '\0': return LEPT_PARSE_EXPECT_VALUE;
	default:   return lept_parse_number(c, v);
	}
}
//获取json类型
int lept_parse(lept_value* v, const char* json) {
	lept_context t;
	assert(v != nullptr);

	t.json = json;
	t.stack = nullptr;
	t.size = t.top = 0;

	lept_init(v);
	lept_parse_whitespace(&t);
	int ret;
	if ((ret = lept_parse_value(&t, v)) == LEPT_PARSE_OK){
		lept_parse_whitespace(&t);
		if (*t.json != '\0') {
			ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
			v->type = LEPT_NULL;
		}
	}
	assert(t.top == 0);
	free(t.stack);
	return ret;
}

void lept_free(lept_value* v) {
	assert(v != nullptr);
	if (v->type == LEPT_STRING) {
		free(v->u.s.s);
	}
	v->type = LEPT_NULL;
}

//返回json类型
lept_type lept_get_type(const lept_value *v) {
	assert(v != nullptr);
	return v->type;
}

double lept_get_number(const lept_value* v) {
	assert(v != nullptr && v->type == LEPT_NUMBER);
	return v->u.n;
}

int lept_get_boolean(lept_value* v) {
	return 0;
}

void lept_set_boolean(lept_value* v, int b) {

}

void lept_set_number(lept_value* v, double n) {

}

const char* lept_get_string(const lept_value* v) {
	assert(v != nullptr && v->type == LEPT_STRING);
	return v->u.s.s;
}

size_t lept_get_string_length(const lept_value* v) {
	assert(v != nullptr && v->type == LEPT_STRING);
	return v->u.s.len;
}

void lept_set_string(lept_value* v, const char* s, size_t len){
	assert(v != nullptr && (s != nullptr || len == 0));
	lept_free(v);
	v->u.s.s = (char*)malloc(len + 1);
	memcpy(v->u.s.s, s, len);
	v->u.s.s[len] = '\0';
	v->u.s.len = len;
	v->type = LEPT_STRING;
	cout << v->u.s.s << endl;
}

