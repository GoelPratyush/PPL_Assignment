// Refer to grammar.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "string_utils.h"

Symbol* createSymbol(int symbolTag, char* symbolValue) {
	Symbol* newSymbol = malloc(sizeof(union symbol));

	// Terminal
	if(symbolTag == 0) {
		newSymbol -> terminal = malloc(sizeof(char) * strlen(symbolValue));
		strcpy(newSymbol -> terminal, symbolValue);
	}
	else if(symbolTag == 1) {
		newSymbol -> nonTerminal = malloc(sizeof(char) * strlen(symbolValue));
		strcpy(newSymbol -> nonTerminal, symbolValue);
	}

	return newSymbol;
}

Node* createNode(int symbolTag, char* symbolValue) {
	Node* newNode = malloc(sizeof(struct node));
	newNode -> symbolTag = symbolTag;
	newNode -> symbol = createSymbol(symbolTag, symbolValue);
	newNode -> next = NULL;

	return newNode;
}

void readGrammar(char* filepath) {
  FILE* fptr = fopen("grammar.txt", "r");
  if(fptr == NULL) {
    fprintf(stderr, "File could not be found or does not exist.");
    exit(1);
  }

  // Processing line by line.
  char line[MAX_LINE_LENGTH];   // Line in the file.
  int grammarIndex = 0;   // Index of array grammar where to insert linked list.
  while(fgets(line, MAX_LINE_LENGTH, fptr) != NULL) {
    // Removing new line added by fgets.
    int lineLen = strlen(line);
    line[lineLen - 1] = '\0';

    // Populating array grammar with head of linked list of rule.
    char delimiter[] = " ";
    processLine(line, delimiter, grammarIndex);
    grammarIndex++;
  }

  fclose(fptr);
}

void printSymbol(int symbolTag, Symbol* s) {
	// Terminal
	if(symbolTag == 0) {
		printf("%s", s -> terminal);
	}
	// Non-terminal
	else if(symbolTag == 1) {
		printf("%s", s -> nonTerminal);
	}
}

void printNode(Node* node) {
  printf("[");
  // If terminal symbol
  if(node -> symbolTag == 0) {
    printf("t:");
    printSymbol(node -> symbolTag, node -> symbol);
  }
  // Else if non-terminal symbol
  else if(node -> symbolTag == 1) {
    printf("nt:");
    printSymbol(node -> symbolTag, node -> symbol);
  }
  printf("]");
}

Node* copyNode(Node* srcNode) {
	Node* copyNode = NULL;
	if(srcNode -> symbolTag == 0) {
		copyNode = createNode(srcNode -> symbolTag, (srcNode -> symbol) -> terminal);
	}
	else if(srcNode -> symbolTag == 1) {
		copyNode = createNode(srcNode -> symbolTag, (srcNode -> symbol) -> nonTerminal);
	}
	return copyNode;
}

Node* copyList(Node* headNode) {
	if(headNode == NULL) {
		fprintf(stderr, "Pass a list of non-zero number of elements to copyList.\n");
	}

	Node* copyHead = copyNode(headNode);
	Node* copyTail = copyHead;

	while(headNode != NULL) {
		copyTail -> next = copyNode(headNode);
		copyTail = copyTail -> next;
		headNode = headNode -> next;
	}

	return copyHead;
}

int lenList(Node* headNode) {
	int len = 0;
	while(headNode != NULL) {
		len++;
		headNode = headNode -> next;
	}

	return len;
}

void printList(Node* headNode) {
	printf("<head> [");
	while(headNode != NULL) {
		printNode(headNode);
		if(headNode -> next != NULL) {
			printf(" --> ");
		}
		headNode = headNode -> next;
	}
	printf("]");
}

void printGrammar() {
  for(int i = 0; i < RULE_COUNT; i++) {
    // Pointer to traverse the linked list at grammar[i].
    printList(grammar[i]); printf("\n");
  }
}

void deallocateSymbol(Symbol* s, int symbolTag) {
	// Terminal
	if(symbolTag == 0) {
		free(s -> terminal);
		free(s);
	}
	// Non-terminal
	else if(symbolTag == 1) {
		free(s -> nonTerminal);
		free(s);
	}
}

void deallocateNode(Node* n) {
	deallocateSymbol(n -> symbol, n -> symbolTag);
	free(n);
}

void deallocateList(Node* newNode) {
    if(newNode == NULL) {
		return;
    }
    deallocateList(newNode -> next);
    deallocateNode(newNode);
}

void deallocateGrammar() {
    for(int i = 0; i < RULE_COUNT; i++) {
        deallocateList(grammar[i]);
    }
}
