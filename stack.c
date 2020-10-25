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

void pushn(Stack* s, Node* nodeArray[], int arrayLen) {
	for(int i = 0; i < arrayLen; i++) {
		push(s, nodeArray[i]);
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

int main() {
	Stack* s = createEmptyStack();
	printStack(s); printf("\n");

	pop(s);
	printStack(s); printf("\n");

	readGrammar("sourcecode.txt");

	Node* nodeArray[2];
	nodeArray[0] = copyNode(grammar[0]);
	nodeArray[1] = copyNode(grammar[1]);
	nodeArray[1] = grammar[1];
	push(s, nodeArray[0]);
	printStack(s); printf("\n");
	push(s, nodeArray[1]);
	printStack(s); printf("\n");

	popn(s, 3);
	printStack(s); printf("\n");
}
