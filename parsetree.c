#include <stdlib.h>
#include "parsetree.h"
#include "typeExpressionTable.h"
#include "grammar.h"

// Modify pretty print according to the requirements of assignment
void printTreeNode(TreeNode* treeNode){
    if (treeNode -> symbolTag == 0){
        printf("Symbol name: %s\n", (treeNode -> symbol) -> terminal);
        printf("Terminal\n");
        printf("Lexeme: %s\n", (((treeNode -> treeNodeType) -> terminal) -> token) -> lexeme);
        printf("Line Number: %d\n",(((treeNode -> treeNodeType) -> terminal) -> token) -> lineNum);
    }
    else if (treeNode -> symbolTag != 0){
        printf("Symbol name: %s\n", (treeNode -> symbol) -> nonTerminal);
        printf("Non Terminal\n");
        printf("Type Expression: "); // printTypeExpression(((treeNode -> treeNodeType) -> nonterminal) -> typeExpr);
        printf("Grammar Rule: %d\n",((treeNode -> treeNodeType) -> nonterminal) -> ruleIndex);
    }
        printf("Depth: %d\n", treeNode -> depth);
}

// Print the complete parse tree in preorder fashion
void printParseTree(ParseTree* parseTree){
    if (parseTree == NULL){
        return;
    }
    printDFSTree(parseTree -> root);
}

// Print tree from current node in preorder fashion
void printDFSTree(TreeNode* treeNode){
    if (treeNode == NULL){
        return;
    }
    printTreeNode(treeNode);
    printDFSTree(treeNode -> leftChild);
    printDFSTree(treeNode -> sibling);
}

// Create a parse tree with root node always being <program> non terminal
ParseTree* createParseTree(){
    ParseTree* newParseTree = malloc(sizeof(struct parsetree));
    Symbol* programSymbol = createSymbol(1, "<program>");
    newParseTree -> root = createNonTerminalTreeNode(programSymbol, newParseTree -> root, 0, 0);
    deallocateSymbol(programSymbol, 1);
    return newParseTree;
}

// Create terminal tree node
TreeNode* createTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, Token* token){
    TreeNode* newTreeNode = malloc(sizeof(struct treenode));
    newTreeNode -> symbol = symbol;
    newTreeNode -> symbolTag = 0;

    TreeNodeType* newTreeNodeType = malloc(sizeof(union treenodetype));
    newTreeNodeType -> terminal = createTerminal(token);

    newTreeNode -> treeNodeType = newTreeNodeType;
    newTreeNode -> parent = parent;
    newTreeNode -> leftChild = NULL;
    newTreeNode -> sibling = NULL;
    newTreeNode -> depth = depth;

    return newTreeNode;
}

// Create non terminal tree node
TreeNode* createNonTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, int ruleindex){
    TreeNode* newTreeNode = malloc(sizeof(struct treenode));
    newTreeNode -> symbol = symbol;
    newTreeNode -> symbolTag = 1;

    TreeNodeType* newTreeNodeType = malloc(sizeof(union treenodetype));
    newTreeNodeType -> nonterminal = createNonTerminal(ruleindex);

    newTreeNode -> treeNodeType = newTreeNodeType;
    newTreeNode -> parent = parent;
    newTreeNode -> leftChild = NULL;
    newTreeNode -> sibling = NULL;
    newTreeNode -> depth = depth;

    return newTreeNode;
}

// TreeNodeType* createTreeNodeType(int symbolTag){
//     TreeNodeType* newTreeNodeType = (TreeNodeType* ) malloc (sizeof(union treenodetype));
//     if (symbolTag == 0){
//         newTreeNodeType -> terminal = NULL;
//     }
//     else if(symbolTag == 1){
//         newTreeNodeType -> nonterminal = NULL;
//     }
//     return newTreeNodeType;
// }

// Create terminal
Terminal* createTerminal(Token* token){
    Terminal* newTerminal = malloc(sizeof(struct terminal));
    newTerminal -> token = token;
    return newTerminal;
}

// Create non terminal
NonTerminal* createNonTerminal(int ruleIndex){
    NonTerminal* newNonTerminal = malloc(sizeof(struct nonterminal));
    newNonTerminal -> ruleIndex = ruleIndex;
    newNonTerminal -> typeExpr = NULL;
    return newNonTerminal;
}

// deallocate non terminal
void deallocateNonTerminal(NonTerminal* nonterminal){
    if (nonterminal == NULL){
        return;
    }
    deallocateTypeExpression(nonterminal -> typeExpr);
    free(nonterminal);
}

// deallocate terminal
void deallocateTerminal(Terminal* terminal){
    if (terminal==NULL){
        return;
    }
    free(terminal -> token);
    free(terminal);
}

// void deallocateTreeNodeType(TreeNodeType* treeNodeType){

// }
// deallocate tree node from current node in Inorder fashion
void deallocateTreeNode(TreeNode* treeNode){
    if (treeNode == NULL){
        return;
    }
    deallocateSymbol(treeNode -> symbol, treeNode -> symbolTag);
    if (treeNode -> symbolTag == 0){
        deallocateTerminal((treeNode -> treeNodeType) -> terminal);
    }
    else if (treeNode -> symbolTag !=0){
        deallocateNonTerminal((treeNode -> treeNodeType) -> nonterminal);
    }
    free(treeNode -> treeNodeType);
    free(treeNode -> sibling);
    free(treeNode -> leftChild);
    free(treeNode);
}

// deallocate parse tree in Inroder fashion
void deallocateParseTree(ParseTree* parseTree){
    if (parseTree == NULL){
        return;
    }
    deallocateTreeNode(parseTree -> root);
    free(parseTree);
}
