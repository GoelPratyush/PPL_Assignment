// Refer to token.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "tokenizer.h"

// Mapping from enum integer value to enum name.
char* enumValueToName[] =
{
	"PROGRAM",
    "DECLARE",
    "COLON",
    "SEMICOLON",
    "LIST",
    "OF",
    "VARIABLES",
    "ARRAY",
    "SQO",
    "DOT",
    "SQC",
    "INT",
    "BOOL",
    "REAL",
    "JAGGED",
    "R1",
    "VALUE",
    "SIZE",
    "CBO",
    "CBC",
	"RBO",
    "RBC",
    "EQU",
    "ADD",
	"SUB",
    "MUL",
    "DIV",
	"AND",
    "OR",
	"NUM",
	"ID",
    "EPSILON"
};

// Returns 1 if string input is an instantaneous integer value, else returns 0.
int isInstInt(char* lexeme) {
	// If lexeme is an empty string, i.e., epsilon, returning 0.
	if(strlen(lexeme) == 0) {
		return 0;
	}
    for(int i = 0; i < strlen(lexeme); i++) {
        if(isdigit(lexeme[i]) == 0) {
            // Not an instantaneous integer value.
            return 0;
        }
    }
    return 1;
}

// Returns 1 if lexeme is a valid variable identifier name, else returns 0.
int isValidVarID(char* lexeme) {
	if(isInstInt(&lexeme[0])) {
		return 0;
	}
	return 1;
}

// Make sure the Token struct returned is freed after use.
Token* createNewToken(char lexeme[], int lineNum) {
	Token* newToken = malloc(sizeof(struct token));

	if(strcmp(lexeme, "program") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = PROGRAM;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "declare") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = DECLARE;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, ":") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = COLON;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
	}

	else if(strcmp(lexeme, ";") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = SEMICOLON;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
	}

    else if(strcmp(lexeme, "list") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = LIST;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "of") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = OF;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "variables") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = VARIABLES;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "array") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = ARRAY;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "[") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = SQO;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "..") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = DOT;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "]") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = SQC;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "integer") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = INT;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "boolean") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = BOOL;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "real") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = REAL;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme,"jagged") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = JAGGED;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "R1") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = R1;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "values") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = VALUE;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "size") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = SIZE;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "{") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = CBO;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "}") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = CBC;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "(") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = RBO;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, ")") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = RBC;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "=") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = EQU;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "+") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = ADD;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "-") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = SUB;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "*") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = MUL;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "/") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = DIV;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "&&&") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = AND;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(strcmp(lexeme, "|||") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = OR;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = INT_MIN;
	    newToken -> next = NULL;
    }

    else if(isInstInt(lexeme)) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = NUM;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = atoi(lexeme);
	    newToken -> next = NULL;
    }

	else if(strcmp(lexeme, "") == 0) {
		newToken -> lineNum = lineNum;
	    newToken -> tokenType = EPSILON;
	    strcpy(newToken -> lexeme, lexeme);
	    newToken -> instInt = atoi(lexeme);
	    newToken -> next = NULL;
	}

	else {
		printf("%s: %d\n", lexeme, strlen(lexeme));
		if(isValidVarID(lexeme) && strcmp(lexeme, "-")) {
			newToken -> lineNum = lineNum;
		    newToken -> tokenType = ID;
		    strcpy(newToken -> lexeme, lexeme);
		    newToken -> instInt = atoi(lexeme);
		    newToken -> next = NULL;
		}
		else {
			fprintf(stderr, "Something's wrong with the sourcecode or tokenizer.\n");
		}
	}

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

	if(headToken != NULL) {
		fprintf(stderr, "Make sure headToken has not been allocated memory and is initialized to NULL to avoid memory leaks.\n");
	}

    char currentLexeme[MAX_LEXEME_LEN];     // Current lexeme being read from source code file.
    Token* tailToken = headToken;           // Pointer that points to the end of the current linked list, so new token can be appended.
    int lineNum = 1;

    while(fscanf(fptr, "%s", currentLexeme) != -1) {
		if(tailToken == NULL) {
            // If head and tail are both NULL, creating new token and
            // assigning both head and tail to it.
            headToken = createNewToken(currentLexeme, lineNum);
            tailToken = headToken;
        }
		else {
            tailToken -> next = createNewToken(currentLexeme, lineNum);
            tailToken = tailToken -> next;
        }

		// Incrementing lineNum on encountering a '\n' character.
        char nl = getc(fptr);
        if(nl == '\n'){
            lineNum++;
        }
	}

	return headToken;
}

void imputeEpsilonTokens(Token* headToken, Token* leftToken, Token* rightToken) {
	// Checking that list has at least 2 nodes.
	if(headToken -> next == NULL) {
		fprintf(stderr, "Ensure token stream has at least 2 tokens before using imputeEpsilonToken.\n");
		return;
	}

	// 2 pointers to traverse the list checking for matches of
	// [leftToken] --> [rightToken] so that token EPSILON can be inserted in
	// between as [leftToken] --> [EPSILON] --> [rightToken].
	Token* leftTraversePointer = headToken;
	Token* rightTraversePointer = headToken -> next;

	while(rightTraversePointer != NULL) {
		// Handling all three cases in a general way.
		// 1. CBO <insert EPSILON> SEMICOLON
		// 2. SEMICOLON <insert EPSILON> SEMICOLON
		// 3. SEMICOLON <insert EPSILON> CBC
		if((leftTraversePointer -> tokenType == leftToken -> tokenType) && (rightTraversePointer -> tokenType == rightToken -> tokenType)) {
			// Pattern found!
			leftTraversePointer -> next = createNewToken("", leftTraversePointer -> lineNum);
			(leftTraversePointer -> next) -> next = rightTraversePointer;

			// Not updating rightTraversePointer as leftTraversePointer has to
			// catch up to right behind it, now that an extra node has been
			// added.
			leftTraversePointer = leftTraversePointer -> next;
		}
		// Checking so that we haven't reached end of list in case the above
		// if statements have been executed and pointers moved.
		if(rightTraversePointer != NULL) {
			leftTraversePointer = leftTraversePointer -> next;
			rightTraversePointer = rightTraversePointer -> next;
		}
	}
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
