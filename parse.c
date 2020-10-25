#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "parse.h"

Index* createIndex(int indexVal) {
	Index* newIndex = malloc(sizeof(struct index));
	newIndex -> indexVal = indexVal;
	newIndex -> next = NULL;

	return newIndex;
}

Index* searchLHS(Symbol* lhsSymbol) {
	Index* headIndex = NULL;
	Index* tailIndex = headIndex;	// Pointer to append new index structs.
	for(int i = 0; i < RULE_COUNT; i++) {
		if(!strcmp(lhsSymbol -> nonTerminal, (grammar[i] -> symbol) -> nonTerminal) && tailIndex == NULL) {
			headIndex = createIndex(i);
			tailIndex = headIndex;
		}
		else if(!strcmp(lhsSymbol -> nonTerminal, (grammar[i] -> symbol) -> nonTerminal) && tailIndex != NULL) {
			tailIndex -> next = createIndex(i);
			tailIndex = tailIndex -> next;
		}
	}

	return headIndex;
}

void printIndexList(Index* headIndex) {
	while(headIndex != NULL) {
		printf("%d ", headIndex -> indexVal);
		headIndex = headIndex -> next;
	}
}

void deallocateIndexList(Index* headIndex) {
	if(headIndex == NULL) {
		return;
	}
	free(headIndex);
}

/* int main() {
	// Populates global array of linked lists grammar.
    readGrammar("grammar.txt");
	Symbol* searchSymbol = createSymbol(1, "<variable>");
	Index* headIndex = searchLHS(searchSymbol);
	printIndexList(headIndex);
	deallocateIndexList(headIndex);
}
*/
