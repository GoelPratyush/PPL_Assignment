/* We can reuse the struct node defined in globals.h. Instead of using it as a
    node of a linked list, using it as a node of a stack.
    Stack accepts pushing and popping of terminals and non-terminals.
*/

// Implementing stack using linked list with pointers to head and tail.
typedef struct stack {
    Node* headNode;
    Node* tailNode;
} Stack;

// Creates and returns pointer to an empty stack.
Stack* createEmptyStack();

// Returns 1 if stack is empty, else returns 0.
int isEmpty(Stack* s);

// Returns pointer to node at top of stack.
Node* top(Stack* s);

// Pushes node onto stack.
void push(Stack* s, Node* nodeToPush);

// Pops node from stack.
void pop(Stack* s);

// Deallocates memory allocated to all nodes of stack.
void deallocateList(Node* headNode);

// Deallocates memory allocated to stack.
void deallocateStack(Stack* s);
