#include <stdio.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"
#include "stack.h"
#include "tokenizer.h"
#include "parsetree.h"
#include "traversetree.h"

int main() {
	int response = 0;
	do {
		printf("Options available are:\n");
		printf("\t[0] Exit\n");
		printf("\t[1] Create parse tree\n");
		printf("\t[2] Construct type expression table and check for type errors\n");
		printf("\t[3] Print parse tree\n");
		printf("\t[4] Print type expression table\n");
		printf("Enter the number (0/1/2/3/4) corresponding to your choice of option: ");
		scanf("%d", &response);
	} while(response != 0 && response != 1 && response != 2 && response != 3 && response != 4);

	if(response == 0) {
		printf("\nExiting...\n");

		return 0;
	}
	else if(response == 1) {
		printf("\nCreating parse tree...\n");

		readGrammar("grammar.txt");

		Token* headToken = NULL;
		headToken = tokeniseSourcecode("sourcecode.txt", headToken);

		Stack* s = createEmptyStack();
		ParseTree* parseTree = createParseTree();
		ruleMatch(parseTree -> root, 0, headToken, s);

		printf("Parse tree is created successfully.\n");

		deallocateParseTree(parseTree);

		return 0;
	}
	else if(response == 2) {
		printf("\nConstructing type expression table and checking for type errors...\n");

		// TODO

		return 0;
	}
	else if(response == 3) {
		printf("\nPrinting parse tree...\n");

		readGrammar("grammar.txt");

		Token* headToken = NULL;
		headToken = tokeniseSourcecode("sourcecode.txt", headToken);

		Stack* s = createEmptyStack();
		ParseTree* parseTree = createParseTree();
		ruleMatch(parseTree -> root, 0, headToken, s);

		printParseTree(parseTree);

		printf("\nParse tree is created and printed successfully.\n");

		deallocateParseTree(parseTree);

		return 0;
	}
	else if(response == 4) {
		printf("\nPrinting type expression table...\n");

		readGrammar("grammar.txt");

		// TODO

		return 0;
	}
}
