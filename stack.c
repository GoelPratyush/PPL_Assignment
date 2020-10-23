#include "stack.h"

Stack* createEmptyStack() {
    Stack* newStack = malloc(sizeof(struct stack));
    newStack -> headNode = NULL;
    newStack -> tailNode = NULL;
}

int isEmpty(Stack* s) {
    if(s -> headNode == NULL && s -> tailNode) {
        return 1;
    }
    return 0;
}

Node* top(Stack* s) {
    return s -> tailNode;
}

void push(Stack* s, Node* nodeToPush) {
    (s -> tailNode) -> next = nodeToPush
    s -> tailNode = (s -> tailNode) -> next;
}

void pop(Stack* s) {
    if(isEmpty(s)) {
        return s;
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

void deallocateStack(Stack* s) {
    deallocateList(s -> headNode);
    free(s);
}
