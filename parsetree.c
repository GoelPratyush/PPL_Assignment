#include "parsetree.h"
#include "typeExpressionTable.h"

void printTreeNode(TreeNode* treeNode){

}

void printParseTree(ParseTree* parseTree){

}

ParseTree* createParseTree(TreeNode* root){
    ParseTree* newParseTree = (ParseTree* ) malloc (sizeof(struct ParseTree));
    Symbol* programSymbol = createSymbol(1, "<program>")
    newParseTree -> root = createNonTerminalTreeNode(programSymbol, 1, NULL, 0)
    deallocateSymbol(programSymbol, 1)
    return newParseTree;
}

TreeNode* createTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, Token* token){
    TreeNode* newTreeNode = (TreeNode* ) malloc (sizeof(struct TreeNode));
    newTreeNode -> symbol = symbol;
    newTreeNode -> symbolTag = 0;

    TreeNodeType* newTreeNodeType = (TreeNodeType* ) malloc (sizeof(union TreeNodeType));
    newTreeNodeType -> terminal = createTerminal(token);

    newTreeNode -> treeNodeType = newTreeNodeType;
    newTreeNode -> parent = parent;
    newTreeNode -> leftChild = NULL;
    newTreeNode -> sibling = NULL;
    newTreeNode -> depth = depth;

    deallocateTreeNodeType(newTreeNodeType);
    return newTreeNode;
}

TreeNode* createNonTerminalTreeNode(Symbol* symbol, TreeNode* parent, int depth, int ruleindex){
    TreeNode* newTreeNode = (TreeNode* ) malloc (sizeof(struct TreeNode));
    newTreeNode -> symbol = symbol;
    newTreeNode -> symbolTag = 1;

    TreeNodeType* newTreeNodeType = (TreeNodeType* ) malloc (sizeof(union TreeNodeType));
    newTreeNodeType -> nonterminal = createNonTerminal(ruleindex);

    newTreeNode -> treeNodeType = newTreeNodeType;
    newTreeNode -> parent = parent;
    newTreeNode -> leftChild = NULL;
    newTreeNode -> sibling = NULL;
    newTreeNode -> depth = depth;

    deallocateTreeNodeType(newTreeNodeType);
    return newTreeNode;
}

// TreeNodeType* createTreeNodeType(int symbolTag){
//     TreeNodeType* newTreeNodeType = (TreeNodeType* ) malloc (sizeof(union TreeNodeType));
//     if (symbolTag == 0){
//         newTreeNodeType -> terminal = NULL;
//     }
//     else if(symbolTag == 1){
//         newTreeNodeType -> nonterminal = NULL;
//     }
//     return newTreeNodeType;
// }

Terminal* createTerminal(Token* token){
    Terminal* newTerminal = (Terminal* ) malloc (sizeof(struct Terminal));
    newTerminal -> token = createNewToken(token);
    return newTerminal;
}

NonTerminal* createNonTerminal(int ruleindex){
    NonTerminal* newNonTerminal = (NonTerminal* ) malloc (sizeof(struct NonTerminal));
    newNonTerminal -> ruleindex = ruleindex;
    newNonTerminal -> typeExpre = NULL;
    return newTerminal;
}

void deallocateNonTerminal(NonTerminal* nonterminal){
    if (nonterminal == NULL){
        return;
    }
    deallocateTypeExpression(nonterminal -> typeExpre);
    free(nonterminal);
}

void deallocateTerminal(Terminal* terminal){
    if (terminal==NULL){
        return;
    }
    free(terminal -> token);
    free(terminal);
}

// void deallocateTreeNodeType(TreeNodeType* treeNodeType){

// }

void deallocateTreeNode(TreeNode* treeNode){
    if (treeNode == NULL){
        return;
    }
    deallocateSymbol(treeNode -> symbol);
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

void deallocateParseTree(ParseTree* parsetree){
    if (parsetree == NULL){
        return;
    }
    deallocateTreeNode(parsetree -> root);
    free(parseTree);
}