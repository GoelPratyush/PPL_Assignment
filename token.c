// Refer to token.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "token.h"

// Mapping from enum integer value to enum name.
char* enumValueToName[] =
{
    "DECLARE",
    "COLON",
    "SEMICOLON",
    "LIST",
    "OF",
    "VARIABLES",
    "ID",
    "ARRAY",
    "SQO",
    "DOT",
    "SQC",
    "NUM",
    "INT",
    "BOOL",
    "REAL",
    "JAGGED",
    "R1",
    "VALUE",
    "SIZE",
    "CBO",
    "CBC",
    "RBC",
    "RBO",
    "EQU",
    "ADD",
    "MUL",
    "DIV",
    "OR",
    "AND"
};

// Returns 1 if string input is an instantaneous integer value, else returns 0.
int isInstInt(char* lexeme) {
    for(int i = 0; i < strlen(lexeme); i++) {
        if(isdigit(lexeme[i]) == 0) {
            // Not an instantaneous integer value.
            return 0;
        }
    }
    return 1;
}

// Make sure the Token struct returned is freed after use.
Token* createNewToken(TokenType tokenType, char lexeme[], int lineNum, int instInt) {
    // Allocating memory for new token.
    Token* newToken = malloc(sizeof(struct token));
    newToken -> lineNum = lineNum;
    newToken -> tokenType = tokenType;
    strcpy(newToken -> lexeme, lexeme);
    newToken -> instInt = instInt;
    newToken -> next = NULL;

    return newToken;
}

// Make sure the token you pass to this function has not been allocated memory
// and is initialized to NULL to avoid memory leaks.
Token* tokeniseSourcecode(char* filepath, Token* headToken) {
    FILE* fptr = fopen(filepath, "r");
    if(fptr == NULL) {
        fprintf(stderr, "File could not be found or does not exist.");
        exit(1);
    }

    char currentLexeme[MAX_LEXEME_LEN];     // Current lexeme being read from source code file.
    Token* tailToken = headToken;               // Pointer that points to the end of the current linked list, so new token can be appended.
    int lineNum = 1;

    while(fscanf(fptr, "%s", currentLexeme) != -1) {
        if(strcmp(currentLexeme, "declare") == 0) {
            if(tailToken == NULL) {
                // If head and tail are both NULL, creating new token and
                // assigning both head and tail to it.
                headToken = createNewToken(DECLARE, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(DECLARE, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "list") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(LIST, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(LIST, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "of") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(OF, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(OF, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "variables") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(VARIABLES, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(VARIABLES, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "integer") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(INT, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(INT, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, ";") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(SEMICOLON, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(SEMICOLON, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme,"jagged") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(JAGGED, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(JAGGED, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "size") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(SIZE, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(SIZE, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "R1") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(R1, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(R1, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "[") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(SQO, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(SQO, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "]") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(SQC, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(SQC, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "..") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(DOT, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(DOT, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, ":") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(COLON, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(COLON, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "{") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(CBO, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(CBO, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "}") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(CBC, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(CBC, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "values") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(VALUE, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(VALUE, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "array") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(ARRAY, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(ARRAY, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "boolean") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(BOOL, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(BOOL, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "real") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(REAL, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(REAL, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "+") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(ADD, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(ADD, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "*") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(MUL, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(MUL, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "/") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(DIV, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(DIV, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "&&&") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(AND, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(AND, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "|||") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(OR, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(OR, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "=") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(EQU, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(EQU, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, "(") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(RBO, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(RBO, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(strcmp(currentLexeme, ")") == 0) {
            if(tailToken == NULL) {
                headToken = createNewToken(RBC, currentLexeme, lineNum, INT_MIN);
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(RBC, currentLexeme, lineNum, INT_MIN);
                tailToken = tailToken -> next;
            }
        }

        else if(isInstInt(currentLexeme)) {
            if(tailToken == NULL) {
                headToken = createNewToken(NUM, currentLexeme, lineNum, atoi(currentLexeme));
                tailToken = headToken;
            }
            else {
                tailToken -> next = createNewToken(NUM, currentLexeme, lineNum, atoi(currentLexeme));
                tailToken = tailToken -> next;
            }
        }

        // Incrementing lineNum on encountering a '\n' character.
        char nl = getc(fptr);
        if(nl == '\n'){
            lineNum++;
        }
    }

    return headToken;

}

void printToken(Token* token) {
    printf("linNum=%-10d lex=%-20s token=%s", token -> lineNum, token -> lexeme, enumValueToName[token -> tokenType]);
}

void printTokenStream(Token* headToken) {
    Token* currentToken = headToken;
    while(currentToken != NULL) {
        printToken(currentToken); printf("\n");
        currentToken = currentToken -> next;
    }
}

// Deallocating memory allocated to every token in tokenStream linked list,
// recursively in reverse.
void deallocateTokenStream(Token* headToken) {
    if(headToken == NULL) {
        return;
    }
    deallocateTokenStream(headToken -> next);
    free(headToken);
}
