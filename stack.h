/* We can reuse the struct node defined in globals.h. Instead of using it as a
    node of a linked list, using it as a node of a stack.
    Stack accepts pushing and popping of terminals and non-terminals.
*/

#ifndef STACK_H
#define STACK_H

// Implementing stack using linked list with pointer to head.
typedef struct stack {
    Node* headNode;
} Stack;

// Creates and returns pointer to an empty stack.
Stack* createEmptyStack();

// Returns 1 if stack is empty, else returns 0.
int isEmpty(Stack* s);

// Prints stack to stdout.
void printStack(Stack* s);

// Returns pointer to node at top of stack.
Node* top(Stack* s);

// Pushes node onto stack.
void push(Stack* s, Node* nodeToPush);

// Pushes nodes from linked list onto stack in left to right order (head to
// NULL). Useful for rightmost derivation.
void pushn(Stack* s, Node* headNode);

// Pushes nodes from linked list recursively onto stack in right to left order
// (NULL to head). Useful for leftmost derivation.
void pushnReverse(Stack* s, Node* headNode);

// Pops node from stack.
void pop(Stack* s);

// Pops n nodes from stack.
void popn(Stack* s, int n);

// Deallocates memory allocated to stack.
void deallocateStack(Stack* s);

#endif
