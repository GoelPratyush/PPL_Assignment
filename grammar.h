// Creates a new symbol for terminal/non-terminal.
Symbol* createSymbol(int symbolTag, char* symbolValue);

// Creates a new node of the linked list.
Node* createNode(int symbolTag, char* symbolValue);

// Reads grammar.txt and populates array of linked lists grammar.
void readGrammar(char* filepath);

// Pretty prints symbol value in a struct of type Symbol to stdout.
void printSymbol(int symbolTag, Symbol* s);

// Pretty prints node to stdout.
void printNode(Node* node);

// Pretty prints array of linked lists grammar to stdout.
void printGrammar();

// Deallocates union symbol in node.
void deallocateSymbol(Symbol* s, int symbolTag);

// Deallocates a node.
void deallocateNode(Node* n);

// IMPORTANT:
// Remember to deallocate the linked list from the last node to the first node
// (otherwise you'll get a memory leak) -- basically in reverse order of
// allocation.
// Keep in mind before deallocating a struct node:
// 1. Deallocate the string in the union first.
// 2. Then deallocate the union.
// 3. Only then deallocate the node.
void deallocateList(Node* headNode);

// Iterates over each list in grammar and freeing it recursively in reverse.
void deallocateGrammar();
