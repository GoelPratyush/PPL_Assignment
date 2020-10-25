// Refer to string_utils.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"

#define ARROW "===>"          // Separator between LHS and RHS of production rule.

int isTerminal(char s[]) {
  int len = strlen(s);

  if(len <= 0) {
    fprintf(stderr, "Length of string must be positive.");
    exit(1);
  }

  // Terminals must all be in uppercase.
  int flagAllUpper = 1;
  for(int i = 0; i < len; i++) {
    // ASCII range for uppercase letters is [65, 90].
    if(s[i] < 65 || s[i] > 90) {
      flagAllUpper = 0;
      break;
    }
  }

  return flagAllUpper;
}

int isNonTerminal(char s[]) {
  int len = strlen(s);

  if(len <= 0) {
    fprintf(stderr, "Length of string must be positive.");
    exit(1);
  }

  // Non-terminal within angle brackets.
  if(s[0] != '<' || s[len - 1] != '>') {
    return 0;
  }

  return 1;
}

void processLine(char line[], char delimiter[], int grammarIndex) {
  // Getting the first symbol in line.
  char* symbolValue = strtok(line, delimiter);

  // IMPORTANT:
  // Remember to deallocate the linked list from the last node to the first node
  // (otherwise you'll get a memory leak) -- basically in reverse order of
  // allocation.
  // Keep in mind before deallocating a struct node:
  // 1. Deallocate the string in the union first.
  // 2. Then deallocate the union.
  // 3. Only then deallocate the node.


  // Inserting first symbol in a node.
  // Allocating space for node.
  Node* headNode = createNode(1, symbolValue);

  // Pointer to iterate over the linked list.
  Node* currentNode = headNode;

  // Getting other symbols in same line.
  while(symbolValue != NULL) {
    // Handling symbols other than arrow.
    if(strcmp(symbolValue, ARROW)) {
      if(isTerminal(symbolValue)) {
        // printf("%s is a terminal.\n", symbol);
        // Inserting next symbol in a node.
        // Allocating space for node.
		Node* newNode = createNode(0, symbolValue);

        // Connecting newNode to the linked list.
        currentNode -> next = newNode;
        currentNode = newNode;
      }
      else if(isNonTerminal(symbolValue)) {
        // printf("%s is a non-terminal.\n", symbol);
        // Inserting next symbol in a node.
        // Allocating space for node.
        Node* newNode = createNode(1, symbolValue);

        // Connecting newNode to the linked list.
        currentNode -> next = newNode;
        currentNode = newNode;
      }
    }
    symbolValue  = strtok(NULL, delimiter);   // Getting next symbol in line.
  }

  // Array grammar is available here as it is a global variable.
  // Adding head node of linked list to grammar[grammarIndex].
  grammar[grammarIndex] = headNode;
}
