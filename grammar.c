// Refer to grammar.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "grammar.h"
#include "string_utils.h"

void printNode(Node* node) {
  printf("[");
  // If terminal symbol
  if(node -> symbolTag == 0) {
    printf("t:");
    printf("%s", (node -> symbol) -> terminal);
  }
  // Else if non-terminal symbol
  else if(node -> symbolTag == 1) {
    printf("nt:");
    printf("%s", (node -> symbol) -> nonTerminal);
  }
  printf("]");
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

void printGrammar() {
  for(int i = 0; i < RULE_COUNT; i++) {
    // Pointer to traverse the linked list at grammar[i].
    Node* currentNode = grammar[i];

    while(currentNode != NULL) {
      printNode(currentNode);
      if(currentNode -> next != NULL) {
        printf(" --> ");
      }
      currentNode = currentNode -> next;
    }

    printf("\n");
  }
}

void deallocateList(Node* headNode) {
    if(headNode -> next == NULL) {
        return;
    }
    deallocateList(headNode -> next);
    free(headNode -> symbol);
    free(headNode);
}

void deallocateGrammar() {
    for(int i = 0; i < RULE_COUNT; i++) {
        deallocateList(grammar[i]);
    }
}
