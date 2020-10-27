#include "globals.h"
#include "typeExpressionTable.h"
#include "tokenizer.h"

typedef struct{
    Symbol* symbol; // Symbol name of terminal ya non terminal according to grammar.txt
    TreeNode * parent; // Pointer to the parent node
    TreeNode * leftChild; // Pointer to left child
    TreeNode * sibling; // Pointer to sibling node
    int tag; // 0 if terminal and 1 if non terminal
    NodeType type; // This is tag union to store the data corresponding to terminal or a non terminal
    int depth; // depth of root node is 0
} TreeNode;

typedef union{
    Terminal terminal;
    NonTerminal nonterminal;
} NodeType;

// In case of terminal we only require the token to get the Line number in sourcecode.txt and name of lexeme
typedef struct{
    Token token;
} Terminal;

// From nonterminal node we require to store the type Expression and the rule number in grammar.txt
typedef struct{
    TypeExpression typeExpr;
    int ruleNumber;
} NonTerminal;