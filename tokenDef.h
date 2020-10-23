//#ifndef _LEXERDEF_
#define _LEXERDEF_

#include <stdio.h>
#include <stdlib.h>

#define total_token_types 27

typedef enum
{

    DECLARE,
    COLON,
    SEMICOLON,
    LIST,
    OF,
    VARIABLES,
    ID,
    ARRAY,
    SQO,
    DOT,
    SQC,
    NUM,
    INT,
    BOOL,
    REAL,
    JAGGED,
    R1,
    VALUE,
    SIZE,
    CBO,
    CBC,
    RBC,
    RBO,
    EQU,
    ADD,
    MUL,
    DIV,
    OR,
    AND

    
} tokenType;

//For storing the value if TokenType is number
typedef union{
    int num;
    float r_num;
}Value;

struct token{
	tokenType type; 
	int valueType; //Valuetype: 0 for int, 1 for real, -1 for other, -2 for ERROR
	int line_no; //Line number of the token
	char lexeme[10]; //Actual Lexeme
    //char stat_type //type of the statement this token is part of
	//Value* value; //For integers and real numbers
    struct token* next;
};

typedef struct token token;

/*struct tokenStream
{
    token tk;
    tokenStream* next;
}*/

