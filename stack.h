/* We can reuse the struct node defined in globals.h. Instead of using it as a
    node of a linked list, using it as a node of a stack.
    Stack accepts pushing and popping of terminals and non-terminals.
*/

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

// Pushes nodes in nodeArray onto stack in left to right order.
void pushn(Stack* s, Node* nodeArray[], int arrayLen);

// Pops node from stack.
void pop(Stack* s);

// Pops n nodes from stack.
void popn(Stack* s, int n);

// Deallocates memory allocated to stack.
void deallocateStack(Stack* s);
