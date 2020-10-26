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
	Node* copyNodeToPush = copyNode(nodeToPush);	// Don't want to push actual node structs of grammar linked lists onto stack.
    copyNodeToPush -> next = s -> headNode;
	s -> headNode = copyNodeToPush;
}

void pushn(Stack* s, Node* headNode) {
	while(headNode != NULL) {
		// Can directly push headNode here because push handles the copying. Not
		// using copyNode here because we don't want a copy of a copy (waste of
		// memory).
		push(s, headNode);
		headNode = headNode -> next;
	}
}

void pushnReverse(Stack* s, Node* headNode) {
	if(headNode == NULL) {
		return;
	}
	pushnReverse(s, headNode -> next);
	push(s, headNode);
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
