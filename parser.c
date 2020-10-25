// Refer to parser.h for documentation on functions in this file.

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"

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

/* int main() {
	// Populates global array of linked lists grammar.
    readGrammar("grammar.txt");
	Symbol* searchSymbol = createSymbol(1, "<com>");
	printf("%d\n", searchLHS(searchSymbol, 30));
}
*/
