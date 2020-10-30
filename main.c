#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"
#include "stack.h"
#include "tokenizer.h"
#include "parsetree.h"
#include "traversetree.h"

int main(int argc, char** argv) {
	int response = 0;

	if(argc != 2) {
		printf("Usage: ./main <test_file>\n");
		return 0;
	}

	char* filename = malloc(sizeof(char) * strlen(argv[1]));
	strcpy(filename, argv[1]);

	int isFirstIter = 1;
	do {
		if(!isFirstIter) {
			// Printing separator line.
			for(int i = 0; i < 100; i++) {
				printf("-");
			}
			printf("\n");
		}
		else {
			isFirstIter = 0;
		}

		printf("Options available are:\n");
		printf("\t[0] Exit\n");
		printf("\t[1] Create parse tree\n");
		printf("\t[2] Construct type expression table and check for type errors\n");
		printf("\t[3] Print parse tree\n");
		printf("\t[4] Print type expression table\n");
		printf("Enter the number (0/1/2/3/4) corresponding to your choice of option: ");
		scanf("%d", &response);

		if(response == 0) {
			printf("\nExiting...\n");
		}
		else if(response == 1) {
			printf("\nCreating parse tree...\n");

			readGrammar("grammar.txt");

			Token* headToken = NULL;
			headToken = tokeniseSourcecode(filename, headToken);

			Stack* s = createEmptyStack();
			ParseTree* parseTree = createParseTree();
			ruleMatch(parseTree -> root, 0, headToken, s);

			printf("Parse tree is created successfully.\n");

			deallocateParseTree(parseTree);
		}
		else if(response == 2) {
			printf("\nConstructing type expression table and checking for type errors...\n");

			readGrammar("grammar.txt");

			Token* headToken = NULL;
			headToken = tokeniseSourcecode(filename, headToken);

			Stack* s = createEmptyStack();
			ParseTree* parseTree = createParseTree();
			ruleMatch(parseTree -> root, 0, headToken, s);

			printf("Parse tree is created successfully.\n");

			traverseParseTree(parseTree->root, 0);

			deallocateParseTree(parseTree);
		}
		else if(response == 3) {
			printf("\nPrinting parse tree...\n");

			readGrammar("grammar.txt");

			Token* headToken = NULL;
			headToken = tokeniseSourcecode(filename, headToken);

			Stack* s = createEmptyStack();
			ParseTree* parseTree = createParseTree();
			ruleMatch(parseTree -> root, 0, headToken, s);

			printParseTree(parseTree);

			printf("\nParse tree created and printed successfully.\n");

			deallocateParseTree(parseTree);
		}
		else if(response == 4) {
			printf("\nPrinting type expression table...\n");

			readGrammar("grammar.txt");

			Token* headToken = NULL;
			headToken = tokeniseSourcecode(filename, headToken);

			Stack* s = createEmptyStack();
			ParseTree* parseTree = createParseTree();
			ruleMatch(parseTree -> root, 0, headToken, s);

			traverseParseTree(parseTree->root, 1);

			deallocateParseTree(parseTree);
		}
	} while(response != 0);

	free(filename);

	return 0;
}
