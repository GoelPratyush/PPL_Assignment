// Refer to parser.h for documentation on functions in this file.

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"
#include "stack.h"
#include "string_utils.h"
#include "tokenizer.h"

static Token* temp = NULL; // Calling rule match recursively and we require to maintain "temp" location after recursive calls

int searchLHS(Symbol* lhsSymbol, int startIndexForSearch) {
	// Searching from startIndexForSearch to end of grammar.
	for(int i = startIndexForSearch; i < RULE_COUNT; i++) {
		if(!strcmp(lhsSymbol -> nonTerminal, (grammar[i] -> symbol) -> nonTerminal)) {
			return i;
		}
	}
	// Looping back and searching from 0 to startIndexForSearch - 1.
	for(int i = 0; i < startIndexForSearch; i++) {
		if(!strcmp(lhsSymbol -> nonTerminal, (grammar[i] -> symbol) -> nonTerminal)) {
			return i;
		}
	}

	return -1;
}

int ruleMatch(int ruleIndex, Token* currentToken, Stack* s) {
	temp = currentToken;
	//pop(s);

	int count = 0;

	pushnReverse(s, grammar[ruleIndex] -> next);
	count += lenList(grammar[ruleIndex] -> next);

	// printf("Start of ruleMatch:\n"); printStack(s); printf("\n\n");
	// printf("\n%d\n", count);
	// return -1;

	// Token* temp = currentToken;

	while(count) {
		// printTokenStream(temp);
		// top(s) is a terminal.
		printf("When in while loop \n");
		printStack(s);
		printf("\n\n");
		if(top(s) -> symbolTag == 0) {
			// If top of stack matches temp token.
			if(strcmp((top(s) -> symbol) -> terminal, enumToString(temp -> tokenType)) == 0) {
				// MATCH!
				printf("Before:\n"); printTokenStream(temp); printf("\n");
				temp = temp -> next;
				printf("After:\n"); printTokenStream(temp); printf("\n");
				pop(s);
				printf("If terminal and match then pop \n");
				printStack(s);
				printf("\nhere count is %d and will be reduced to %d", count, count-1);
				printf("\n\n");
				count--;
			}

			// If top of stack does not match temp token.
			else if(strcmp((top(s) -> symbol) -> terminal, enumToString(temp -> tokenType)) != 0) {
				printf("top symbol that did not match=%s\n", (top(s) -> symbol) -> terminal);
				printToken(temp);printf("\n");
				// printf("enum to string=%s\n", enumToString(temp -> tokenType));
				// printf("END\n");
				
				printf("Before removing the complete %d nodes from stack\n", count);
				printStack(s);
				printf("\n\n");
				popn(s, count);
				printf("After removing the complete %d nodes from stack\n", count);
				printStack(s);
				printf("\n\n");
				temp = currentToken;
				return 0;
			}
		}

		// top(s) is a non-terminal.
		else if(top(s) -> symbolTag == 1) {
			// printf("Non-terminal if:\n"); printStack(s); printf("\n\n");
			printf("top non terminal symbol expanded=%s\n", (top(s) -> symbol) -> terminal);
			int startIndex = searchLHS(top(s) -> symbol, ruleIndex + 1);
			// printf("startIndex=%d\n", startIndex);

			// Storing currentTop before popping it.
			Node* currentTop = copyNode(top(s));
			pop(s);
			// printf("After poping the non terminal\n");
			// printStack(s);
			// printf("\n\n");

			int nextIndex = startIndex;

			int retVal = 0;
			do {
				// printf("do while:\n");
				// printf("nextIndex=%d\n", nextIndex);
				// printf("token="); printToken(temp); printf("\n");
				// printf("stack="); printStack(s); printf("\n\n");
				retVal = ruleMatch(nextIndex, temp, s);
				if(retVal == 0) {
					printf("stack when rule match is unsuccessful\n");
					printStack(s);
					printf("\n");
					printf("Top symbol is");
					printNode(currentTop);
					printf("\n\n");
					nextIndex = searchLHS(currentTop -> symbol, nextIndex + 1);
				}
			}
			while(nextIndex != startIndex && retVal == 0);

			// Went through the whole grammar list by expanding rhs of rules recursively, for a given grammar rule. No rule matched, so returning 0.
			if(retVal == 0) {
				if(count >= 1){
					popn(s,count-1);
				}
				temp = currentToken;
				return 0;
			}
			else{
				printf("If the nonterminal is correctly expanded and checked\n");
				printStack(s);
				printf("\nhere count is %d and will be reduced to %d", count, count-1);
				printf("\n\n");
				count--;
			}	
		}
	}

	// RHS matches! Moving to next token in tokenStream.
	// printStack(s);
	currentToken = temp;
	printf("\n\n");
	printToken(currentToken);
	printf("\n\n");
	return 1;
}

/* int main() {
	// Populates global array of linked lists grammar.
    readGrammar("grammar.txt");
	Symbol* searchSymbol = createSymbol(1, "<com>");
	printf("%d\n", searchLHS(searchSymbol, 30));
}
*/
