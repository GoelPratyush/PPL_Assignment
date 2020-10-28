#include <stdlib.h>
#include "parsetree.h"

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
        printf("Type Expression: \n"); // printTypeExpression(((treeNode -> treeNodeType) -> nonterminal) -> typeExpr);
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

// terminals and non terminals of Grammar[i] will be stored in child nodes of the parent node
TreeNode* fillGrammarInNodes(TreeNode* parent, int index, Token* currentToken){
    Node* iterator = grammar[index] -> next;
    TreeNode* newTreeNode;
    // Leftmost child
    //Terminal
    if (iterator -> symbolTag == 0){
        newTreeNode = createTerminalTreeNode(iterator -> symbol, parent, parent -> depth + 1, currentToken);
        parent -> leftChild = newTreeNode;
        currentToken = currentToken -> next;
    }
    // Nonterminal
    else if (iterator -> symbolTag != 0){
        newTreeNode = createNonTerminalTreeNode(iterator -> symbol, parent, parent -> depth + 1, index);
        parent -> leftChild = newTreeNode;
    }
    iterator = iterator -> next;

    // Siblings
    while(iterator != NULL){
        // Terminal
        if (iterator -> symbolTag == 0){
            newTreeNode -> sibling = createTerminalTreeNode(iterator -> symbol, parent, parent -> depth + 1, currentToken);
            currentToken = currentToken -> next;
        }
        // Nonterminal
        else if (iterator -> symbolTag != 0){
            newTreeNode -> sibling = createNonTerminalTreeNode(iterator -> symbol, parent, parent -> depth + 1, index);
        }
        newTreeNode = newTreeNode -> sibling;
        iterator = iterator -> next;
    }
    return parent -> leftChild;
}

// Create a parse tree with root node always being <program> non terminal
ParseTree* createParseTree(){
    ParseTree* newParseTree = malloc(sizeof(struct parsetree));
    // Symbol* programSymbol = createSymbol(1, "<program>");
    newParseTree -> root = createNonTerminalTreeNode(grammar[0] -> symbol, newParseTree -> root, 0, 0);
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
    //free(terminal -> token);
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
    // Terminal
    if (treeNode -> symbolTag == 0){
        printf("LOLita\n");
        deallocateTerminal((treeNode -> treeNodeType) -> terminal);
    }

    // Nonterminal
    else if (treeNode -> symbolTag !=0){
        printf("Lonavala\n");
        deallocateNonTerminal((treeNode -> treeNodeType) -> nonterminal);
    }
    free(treeNode -> treeNodeType);
    deallocateTreeNode(treeNode -> leftChild);
    deallocateTreeNode(treeNode -> sibling);
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
