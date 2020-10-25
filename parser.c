#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"

// Searches for rules in grammar that have LHS as lhsSymbol. Returns indices of
// grammar where the symbols match as a linked list. Make sure you free the
// list of indices returned by searchRule to save memory.
int searchLHS(Symbol* lhsSymbol, int startIndexForSearch);

int searchLHS(Symbol* lhsSymbol, int startIndexForSearch) {
	for(int i = startIndexForSearch + 1; i < RULE_COUNT; i++) {
		if(!strcmp(lhsSymbol -> nonTerminal, (grammar[i] -> symbol) -> nonTerminal)) {
			return i;
		}
	}

	return -1;
}

int main() {
	// Populates global array of linked lists grammar.
    readGrammar("grammar.txt");
	Symbol* searchSymbol = createSymbol(1, "<com>");
	printf("%d\n", searchLHS(searchSymbol, 28));
}
