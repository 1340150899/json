#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h>

//C语言没有命名空间所以枚举用大写字母，类型和函数用小写字母
typedef enum{LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT} lept_type;

//向前声明
typedef struct lept_value lept_value; 
typedef struct lept_member lept_member;

struct lept_value
{
    union 
    {
        //数字
        double n;
        //字符串
        struct 
        {
            char*s;
            size_t len;
        }s;
        // 数组
        struct{
            lept_value* e;
            size_t size;
        }a;
        // object
        struct 
        {
            lept_member* m;
            size_t size;
        }o;
        
    }u;
    // 类型
    lept_type type;
};
//object
struct lept_member
{
    char* k;
    size_t klen;
    lept_value v;
};

//错误码
enum{
    LEPT_PARSE_OK = 0, //返回正常
    LEPT_PARSE_EXPECT_VALUE, //传入的字符串只有空白
    LEPT_PARSE_INVALID_VALUE, //未识别的类型
    LEPT_PARSE_ROOT_NOT_SINGULAR , //空白后含有字符
    LEPT_PARSE_NUMBER_TOO_BIG, //超过double最大值
    LEPT_PARSE_MISS_QUOTATION_MARK,  //字符串中含有 \0
    LEPT_PARSE_INVALID_STRING_ESCAPE,  //无法识别转义符 \ 后面的字符
    LEPT_PARSE_INVALID_STRING_CHAR,  //字符串中有不合法的字符
    LEPT_PARSE_INVALID_UNICODE_HEX,  //utf-8不合法    
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,  //代理对错误
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,  //方括号不成对
    LEPT_PARSE_MISS_KEY,  //对象缺少key
    LEPT_PARSE_MISS_COLON,  //冒号不成对
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET  //花括号不成对
};


#define lept_init(v) do{(v)->type = LEPT_NULL;} while(0)

//解析json
int lept_parse(lept_value* v, const char* json);
//生成
char* lept_stringify(const lept_value* v, size_t* length);

// 获取类型
lept_type lept_get_type(const lept_value* v);


//每个类型的get和set
double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

//free栈
void lept_free(lept_value* v);
#define lept_set_null(v) lept_free(v);


int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);

#endif
