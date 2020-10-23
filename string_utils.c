// Refer to string_utils.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

#define ARROW "===>"          // Separator between LHS and RHS of production rule.

int isTerminal(char s[]) {
  int len = strlen(s);

  if(len <= 0) {
    fprintf(stderr, "Length of string must be positive.");
    exit(1);
  }

  // Terminals must all be in uppercase.
  int flag_all_upper = 1;
  for(int i = 0; i < len; i++) {
    // ASCII range for uppercase letters is [65, 90].
    if(s[i] < 65 || s[i] > 90) {
      flag_all_upper = 0;
      break;
    }
  }

  return flag_all_upper;
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
  char* symbol = strtok(line, delimiter);

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
  Node* headNode = malloc(sizeof(struct node));
  headNode -> symbolTag = 1;  // Non-terminal
  // Allocating space for union.
  headNode -> symbol = malloc(sizeof(union symbol));
  // Allocating space for string in union.
  (headNode -> symbol) -> nonTerminal = malloc(sizeof(char) * strlen(symbol));
  strcpy((headNode -> symbol) -> nonTerminal, symbol);
  headNode -> next = NULL;

  // Pointer to iterate over the linked list.
  Node* currentNode = headNode;

  // Getting other symbols in same line.
  while(symbol != NULL) {
    // Handling symbols other than arrow.
    if(strcmp(symbol, ARROW)) {
      if(isTerminal(symbol)) {
        // printf("%s is a terminal.\n", symbol);
        // Inserting next symbol in a node.
        // Allocating space for node.
        Node* newNode = malloc(sizeof(struct node));
        newNode -> symbolTag = 0;  // Terminal
        // Allocating space for union.
        newNode -> symbol = malloc(sizeof(union symbol));
        // Allocating space for string in union.
        (newNode -> symbol) -> terminal = malloc(sizeof(char) * strlen(symbol));
        strcpy((newNode -> symbol) -> terminal, symbol);
        newNode -> next = NULL;

        // Connecting newNode to the linked list.
        currentNode -> next = newNode;
        currentNode = newNode;
      }
      else if(isNonTerminal(symbol)) {
        // printf("%s is a non-terminal.\n", symbol);
        // Inserting next symbol in a node.
        // Allocating space for node.
        Node* newNode = malloc(sizeof(struct node));
        newNode -> symbolTag = 1;  // Non-terminal
        // Allocating space for union.
        newNode -> symbol = malloc(sizeof(union symbol));
        // Allocating space for string in union.
        (newNode -> symbol) -> nonTerminal = malloc(sizeof(char) * strlen(symbol));
        strcpy((newNode -> symbol) -> nonTerminal, symbol);
        newNode -> next = NULL;

        // Connecting newNode to the linked list.
        currentNode -> next = newNode;
        currentNode = newNode;
      }
    }
    symbol = strtok(NULL, delimiter);   // Getting next symbol in line.
  }

  // Array grammar is available here as it is a global variable.
  // Adding head node of linked list to grammar[grammarIndex].
  grammar[grammarIndex] = headNode;
}
