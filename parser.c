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
#include "parsetree.h"

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

int ruleMatch(TreeNode* parent, int ruleIndex, Token* currentToken, Stack* s) {
	temp = currentToken;
	//Token* temp2 = currentToken;
	int count = 0;

	pushnReverse(s, grammar[ruleIndex] -> next);
	count += lenList(grammar[ruleIndex] -> next);
	///*
	Node* iterator = grammar[ruleIndex] -> next;
	Node* tempNode = copyNode(iterator);
	TreeNode* childTreeNode;
	//Terminal
	if (iterator -> symbolTag == 0){
        childTreeNode = createTerminalTreeNode(tempNode, parent, parent -> depth + 1, temp);
        parent -> leftChild = childTreeNode;
        //temp2 = temp2 -> next;
    }
    // Nonterminal
    else if (iterator -> symbolTag != 0){
        childTreeNode = createNonTerminalTreeNode(tempNode, parent, parent -> depth + 1, ruleIndex);
        parent -> leftChild = childTreeNode;
    }
	//*/

	while(count) {
		// top(s) is a terminal.

		iterator = iterator -> next;
		/*
		printf("When in while loop \n");
		printStack(s);
		printf("\n\n");
		printToken(temp);printf("\n");
		*/
		if(top(s) -> symbolTag == 0) {
			/*
			printf("Before:\n");
			printToken(temp);
			printf("\n");
			*/
			// If top of stack matches temp token.
			if(strcmp((top(s) -> symbol) -> terminal, enumToString(temp -> tokenType)) == 0) {
				// MATCH!
				//printf("Match found\n");
				//printf("Before:\n"); printTokenStream(temp); printf("\n");
				temp = temp -> next;
				//temp2 = temp2 -> next;
				//printf("After:\n"); printTokenStream(temp); printf("\n");
				pop(s);
				count--;
			}

			// If top of stack does not match temp token.
			else if(strcmp((top(s) -> symbol) -> terminal, enumToString(temp -> tokenType)) != 0) {
				//printf("Empty the stack for this rule\n");
				//printf("top symbol that did not match=%s\n", (top(s) -> symbol) -> terminal);
				//printToken(temp);printf("\n");
				// printf("enum to string=%s\n", enumToString(temp -> tokenType));

				popn(s, count);
				deallocateTreeNode(parent -> leftChild);
				parent -> leftChild = NULL;
				temp = currentToken;
				return 0;
			}
		}

		// top(s) is a non-terminal.
		else if(top(s) -> symbolTag == 1) {
			int startIndex = searchLHS(top(s) -> symbol, ruleIndex);
			//printf("If nonterminal\n");
			// Storing currentTop before popping it.
			Node* currentTop = copyNode(top(s));
			pop(s);

			int nextIndex = startIndex;

			int retVal = 0;
			do {
				retVal = ruleMatch(childTreeNode, nextIndex, temp, s);
				if(retVal == 0) {
					/*
					printf("Top node is: \n");
					printNode(currentTop);
					printf("\n");
					*/
					nextIndex = searchLHS(currentTop -> symbol, nextIndex + 1);
				}
			}
			while(nextIndex != startIndex && retVal == 0);

			// Went through the whole grammar list by expanding rhs of rules recursively, for a given grammar rule. No rule matched, so returning 0.
			if(retVal == 0) {
				if(count >= 1){
					popn(s,count-1);
				}
				deallocateTreeNode(parent -> leftChild);
				parent -> leftChild = NULL;
				temp = currentToken;
				return 0;
			}
			else{
				count--;
			}
		}
		///*
		if (count!=0 && iterator != NULL){
			Node* tempNode = copyNode(iterator);
        	if (iterator -> symbolTag == 0){
            	childTreeNode -> sibling = createTerminalTreeNode(tempNode, parent, parent -> depth + 1, temp);
            	//temp2 = temp2 -> next;
        	}
        	// Nonterminal
        	else if (iterator -> symbolTag != 0){
            	childTreeNode -> sibling = createNonTerminalTreeNode(tempNode, parent, parent -> depth + 1, ruleIndex);
        	}
        	childTreeNode = childTreeNode -> sibling;
			//printf("End of while\n");
		}
		//*/
	}
	//printf("Outside while\n");
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
