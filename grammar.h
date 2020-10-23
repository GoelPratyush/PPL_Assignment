// Pretty prints node to stdout.
void printNode(Node* node);

// Reads grammar.txt and populates array of linked lists grammar.
void readGrammar(char* filepath);

// Pretty prints array of linked lists grammar to stdout.
void printGrammar();

// IMPORTANT:
// Remember to deallocate the linked list from the last node to the first node
// (otherwise you'll get a memory leak) -- basically in reverse order of
// allocation.
// Keep in mind before deallocating a struct node:
// 1. Deallocate the string in the union first.
// 2. Then deallocate the union.
// 3. Only then deallocate the node.
void deallocateGrammar();
