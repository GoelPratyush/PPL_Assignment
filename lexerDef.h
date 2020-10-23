//#ifndef _LEXERDEF_
#define _LEXERDEF_

#include <stdio.h>
#include <stdlib.h>

#define total_token_types 45

typedef enum{TERM1, TERM2} Tokentype;

//For storing the value if TokenType is number
typedef union{
    int num;
    float r_num;
}Value;

struct token{
    Tokentype type;
    int valueType;
    int line_no;
    //lexeme stored in case of tokens other than number in which case it's specifics are stored in value
    char* lexeme;
    Value* value;
};

typedef struct token Token;

