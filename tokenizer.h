#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TOKEN_TYPES 29
#define MAX_LEXEME_LEN 20       // Maximum number of characters in a lexeme

// Make sure if you add a new name into the enum, update array enumValueToName
// in token.c.
typedef enum {
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
} TokenType;

typedef struct token {
    TokenType tokenType;
    char lexeme[MAX_LEXEME_LEN];       // Actual lexeme
    int lineNum;        // Line number of the token

    // To store an instantaneous integer value (instantaneous float &
    // instantaneous boolean values are not allowed). Holds INT_MIN if lexeme is
    // anything but an instantaneous integer value.
    int instInt;

    struct token* next;
} Token;

// Returns 1 if string input is an instantaneous integer value, else returns 0.
int isInstInt(char* lexeme);

// Make sure the Token struct returned is freed after use.
// Deallocate memory in the order:
// 1. Deallocate the string lexeme first.
// 2. Then deallocate the struct itself.
Token* createNewToken(TokenType tokenType, char lexeme[], int lineNum, int instInt);

// Goes through sourcecode.txt and returns a linked list of Token structs.
Token* tokeniseSourcecode(char* filepath, Token* headToken);

// Prints a token to stdout.
void printToken(Token* token);

// Prints linked list of tokens to stdout.
void printTokenStream(Token* token);

// Deallocates memory allocated to all tokens in token stream.
void deallocateTokenStream(Token* headToken);
