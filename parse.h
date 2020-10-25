// Struct to hold an index of grammar. This function returns a linked list
// of structs containing indices where lhsSymbol matches LHS symbol of
// grammar.
typedef struct index {
	int indexVal;
	struct index* next;
} Index;

// Creates an instance of struct index.
Index* createIndex(int indexVal);

// Searches for rules in grammar that have LHS as lhsSymbol. Returns indices of
// grammar where the symbols match as a linked list. Make sure you free the
// list of indices returned by searchRule to save memory.
Index* searchLHS(Symbol* lhsSymbol);

// Utility function to print list of indices returned by searchRule.
void printIndexList(Index* headIndex);
