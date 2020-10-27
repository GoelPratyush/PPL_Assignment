#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

// Make sure if you add a new name into the enum, update array enumValueToName
// in token.c.
typedef enum {
    PROGRAM,
    DECLARE,
    COLON,
    SEMICOLON,
    LIST,
    OF,
    VARIABLES,
    ARRAY,
    SQO,
    DOT,
    SQC,
    INT,
    BOOL,
    REAL,
    JAGGED,
    R1,
    VALUE,
    SIZE,
    CBO,
    CBC,
	RBO,
    RBC,
    EQU,
    ADD,
	SUB,
    MUL,
    DIV,
	AND,
    OR,
	NUM,
	ID,
    EPSILON
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

// Returns 1 if lexeme is a valid variable identifier name, else returns 0.
// Invalid identifier if starts with digit.
int isValidVarID(char* lexeme);

// Make sure the Token struct returned is freed after use.
// Deallocate memory in the order:
// 1. Deallocate the string lexeme first.
// 2. Then deallocate the struct itself.
Token* createNewToken(char lexeme[], int lineNum);

// Goes through sourcecode.txt and returns a linked list of Token structs.
Token* tokeniseSourcecode(char* filepath, Token* headToken);

// Adds an EPSILON token in between two consecutive tokens defined by leftToken
// and rightToken, anywhere the pattern appears in tokenStream.
void imputeEpsilonTokens(Token* headToken, Token* leftToken, Token* rightToken);

// Prints a token to stdout.
void printToken(Token* token);

// Prints linked list of tokens to stdout.
void printTokenStream(Token* token);

// Converting from enum int to string using enumValueToName in tokenizer.c
char* enumToString(TokenType tokenType);

// Deallocates memory allocated to all tokens in token stream. Can be used to
// deallocate one token as well, provided its next pointer is NULL.
void deallocateTokenStream(Token* headToken);

#endif
