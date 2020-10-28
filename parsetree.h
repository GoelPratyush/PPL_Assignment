#ifndef PARSETREE_H
#define PARSETREE_H

#include "globals.h"
#include "grammar.h"
#include "typeExpressionTable.h"
#include "tokenizer.h"

typedef struct treenode TreeNode;
typedef struct parsetree ParseTree;
typedef union treenodetype TreeNodeType;
typedef struct terminal Terminal;
typedef struct nonterminal NonTerminal;

typedef struct treenode{
    Symbol* symbol; // Symbol contains token names in all Capitals or non terminal name in <>
    TreeNodeType* treeNodeType; // This is tag union to store the data corresponding to terminal or a non terminal
    int symbolTag; // 0 if terminal and 1 if non terminal

    TreeNode* parent; // Pointer to the parent node
    TreeNode* leftChild; // Pointer to left child
    TreeNode* sibling; // Pointer to sibling node

    int depth; // depth of root node is 0
} TreeNode;

typedef struct parsetree{
    TreeNode* root;
} ParseTree;

typedef union treenodetype{
    Terminal* terminal;
    NonTerminal* nonterminal;
} TreeNodeType;

// In case of terminal we only require the token to get the Line number in sourcecode.txt and name of lexeme
typedef struct terminal{
    Token* token;
} Terminal;

// From nonterminal node we require to store the type Expression and the rule number in grammar.txt
typedef struct nonterminal{
    TypeExpression* typeExpr;
    int ruleIndex;
} NonTerminal;

// Print one tree Node
void printTreeNode(TreeNode* treeNode);

// Print the complete parse tree in preorder fashion
void printParseTree(ParseTree* parseTree);

// Print tree from current node in preorder fashion
void printDFSTree(TreeNode* treeNode);

// terminals and non terminals of Grammar[i] will be stored in child nodes of the parent node
TreeNode* fillGrammarInNodes(TreeNode* parent, int index, Token* currentToken);

// Create a parse tree with root node always being <program> non terminal
ParseTree* createParseTree();

// Create terminal tree node
TreeNode* createTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, Token* token);

// Create non terminal tree node
TreeNode* createNonTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, int ruleindex);

// TreeNodeType* createTreeNodeType(int symbolTag);
// Create terminal
Terminal* createTerminal(Token* token);

// Create non terminal
NonTerminal* createNonTerminal(int ruleindex);

// deallocate non terminal
void deallocateNonTerminal(NonTerminal* nonterminal);

// deallocate terminal
void deallocateTerminal(Terminal* terminal);

// deallocate tree node
void deallocateTreeNode(TreeNode* treeNode);

// deallocate parse tree in Inroder fashion
void deallocateParseTree(ParseTree* parseTree);

#endif
