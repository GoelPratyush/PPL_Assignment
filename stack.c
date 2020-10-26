// Refer to stack.h for documentation on functions in this file.

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "grammar.h"
#include "stack.h"

Stack* createEmptyStack() {
    Stack* newStack = malloc(sizeof(struct stack));
    newStack -> headNode = NULL;

	return newStack;
}

int isEmpty(Stack* s) {
    if(s -> headNode == NULL) {
        return 1;
    }
    return 0;
}

void printStack(Stack* s) {
	Node* currentNode = s -> headNode;	// Pointer to iterate over the list.
	printf("<top> [");
	while(currentNode != NULL) {
		printNode(currentNode);
		if(currentNode -> next != NULL) {
			printf(" ");
		}
		currentNode = currentNode -> next;
	}
	printf("]");
}

Node* top(Stack* s) {
    return s -> headNode;
}

void push(Stack* s, Node* nodeToPush) {
    nodeToPush -> next = s -> headNode;
	s -> headNode = nodeToPush;
}

void pushn(Stack* s, Node* headNode) {
	while(headNode != NULL) {
		push(s, headNode);
		headNode = headNode -> next;
	}
}

void pop(Stack* s) {
    if(isEmpty(s)) {
		printf("WARNING: Cannot pop from empty stack. Returning stack as is.\n");
        return;
    }
	else {
		Node* toDealloc = s -> headNode;
		s -> headNode = (s -> headNode) -> next;
		deallocateNode(toDealloc);
	}
}

void popn(Stack* s, int n) {
	while(n) {
		if(isEmpty(s)) {
			printf("WARNING: Tried to pop more elements from stack than contained.\n");
			break;
		}
		pop(s);
		n--;
	}
}

void deallocateStack(Stack* s) {
    deallocateList(s -> headNode);
    free(s);
}
