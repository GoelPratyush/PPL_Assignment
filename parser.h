#ifndef PARSER_H
#define PARSER_H

#include "stack.h"
#include "tokenizer.h"
#include "parsetree.h"

// Searches for rules in grammar that have LHS as lhsSymbol. Returns indices of
// grammar where the symbols match as a linked list. Make sure you free the
// list of indices returned by searchRule to save memory.
int searchLHS(Symbol* lhsSymbol, int startIndexForSearch);

// Given a grammar rule, checks whether currentToken matches with it.
// IMPORTANT: Before calling this function the first time, make sure stack has
// exactly one token = "<program>"
int ruleMatch(TreeNode* parent, int ruleIndex, Token* currentToken, Stack* stack);

// Function to create parse tree.
// void createParseTree(ParseTree* parseTree, TokenStream* tokenStream);

#endif
