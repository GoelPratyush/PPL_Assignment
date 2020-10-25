// Searches for rules in grammar that have LHS as lhsSymbol. Returns indices of
// grammar where the symbols match as a linked list. Make sure you free the
// list of indices returned by searchRule to save memory.
int searchLHS(Symbol* lhsSymbol, int startIndexForSearch);
