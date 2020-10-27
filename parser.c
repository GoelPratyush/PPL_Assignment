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
	pop(s);

	int count = 0;

	pushnReverse(s, grammar[ruleIndex] -> next);
	count += lenList(grammar[ruleIndex] -> next);

	// printStack(s);
	// printf("\n%d\n", count);
	// return -1;

	Token* temp = currentToken;

	while(count) {
		// top(s) is a terminal.
		if(top(s) -> symbolTag == 0) {
			// Extracting top token from top node of stack.
			Token* topToken = NULL;
			// Making token from node to get tokenType.
			printf("%s\n", (top(s) -> symbol) -> terminal);
			topToken = createNewToken((top(s) -> symbol) -> terminal, -1);

			// If top of stack matches temp token.
			if(topToken -> tokenType == temp -> tokenType) {
				// MATCH!
				temp = temp -> next;
				pop(s);
				count--;
			}

			// If top of stack does not match temp token.
			else if(topToken -> tokenType != temp -> tokenType) {
				printToken(topToken); printf("\n");
				printToken(temp); printf("\n");
				printStack(s);
				popn(s, count);
				deallocateTokenStream(topToken);	// Done with topToken.
				return 0;
			}

			deallocateTokenStream(topToken);	// Done with topToken.
		}

		// top(s) is a non-terminal.
		else if(top(s) -> symbolTag == 1) {
			int startIndex = searchLHS(top(s) -> symbol, ruleIndex + 1);

			// Storing currentTop before popping it.
			Node* currentTop = copyNode(top(s));
			pop(s);
			count--;

			int nextIndex = startIndex;

			int retVal = 0;
			do {
				retVal = ruleMatch(nextIndex, temp, s);
				if(retVal == 0) {
					nextIndex = searchLHS(currentTop -> symbol, nextIndex + 1);
				}
			}
			while(nextIndex != startIndex && retVal == 0);

			// Went through the whole grammar list by expanding rhs of rules recursively, for a given grammar rule. No rule matched, so returning 0.
			if(retVal == 0) {
				return 0;
			}
			else if(retVal == 1) {
				temp = temp -> next;
			}
		}
	}

	// RHS matches! Moving to next token in tokenStream.
	currentToken = temp;

	return 1;
}

/* int main() {
	// Populates global array of linked lists grammar.
    readGrammar("grammar.txt");
	Symbol* searchSymbol = createSymbol(1, "<com>");
	printf("%d\n", searchLHS(searchSymbol, 30));
}
*/
