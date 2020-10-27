#include "tree.h"

typeExpressionTable *initTypeExpressionTable(){
    typeExpressionTable *newTable = (typeExpressionTable*)malloc(sizeof(typeExpressionTable));
    newTable->table = NULL;
    newTable->varNum = 0;
}

// Function expands the table by 10 units
void expandTable(typeExpressionTable *t){
    if(t->varNum == 0){
        t->table = (TypeExpression*)malloc(sizeof(TypeExpression)*10);
    }
    else{
        int initSize = sizeof(TypeExpression)*t->varNum;
        t->table = (TypeExpression*) realloc(t->table, initSize+sizeof(TypeExpression)*10);
    }
}

// Creates a template typeExpression that can be copied for any number of variables that share the same template
// *node points to the first sibling of COLON
TypeExpression *addTypeExpression(TreeNode *node){
    TypeExpression *template = (TypeExpression*)malloc(sizeof(TypeExpression));
    if(strcmp(node->symbol->nonTerminal, "jagged_array1"){

    }
    else{
        node = node->leftChild;
        // If primitive data type, <type> has no sibling
        if(node->sibling){
            // For the case of rectangular array
            // node is at <array> 
            template->lexeme = '\0';
            template->tag = 1;

            // Hard coding for type extraction
            // node->sibling->sibling is <type> node
            if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "INT"))
                template->type->array->dataType = integer;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "BOOL"))
                template->type->array->dataType = boolean;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "REAL"))
                template->type->array->dataType = real;
            else{
                //**********************
                // For the case we have none of INT BOOL REAL in our declaration statement, record as error?
            }


        }
        else{
            // For the case of primitive data type
            // node is at <type>
            template->lexeme[0] = '\0';
            template->tag = 0;
            template->arrayType = notApplicable;
            if(strcmp(node->leftChild->symbol->terminal, "INT"))
                template->type->primitive->dataType = integer;
            else if(strcmp(node->leftChild->symbol->terminal, "BOOL"))
                template->type->primitive->dataType = boolean;
            else if(strcmp(node->leftChild->symbol->terminal, "REAL"))
                template->type->primitive->dataType = real;
            else{
                //**********************
                // For the case we have none of INT BOOL REAL in our declaration statement, record as error?
            }
        }
    }
}

// This function starts at <stmt> node of the parse tree and recursively calls itself for each <stmt> node of the parse tree and populates the typeExpressionTable for each of <stmt>
void declarationStatemets(TreeNode* decStatement){
    // Handling DECLARE LIST and DECLARE separately
    // If DECLARE LIST then the first sibling of DECLARE will be LIST that is a terminal, else it will be <var> which is a non_terminal
    if(decStatement->leftChild->sibling->symbol->tag == 1){
        // For the case of a single variable declared

    }
    else{
        // For the case of list of variables declared
    }

    // If <stmt> has a sibling, it has to be <declaration_stmt>, hence recursively call this function for all <stmt> nodes
    if(decStatement->sibling)
        declarationStatemets(decStatement->sibling->leftChild);
}

void assignmentStatements(TreeNode* assignStatement){

}

void traverseParseTree(TreeNode* head){
    typeExpressionTable *t = initTypeExpressionTable();
    expandTable(t);

    // @VK this is the main function that we are implementing.
    // Implement the function assignmentStatements, change it's declaration and definition as you like.
    // Basically you can pass the node for <assign_stmts> of the parse tree which would essentially be
    // head->leftChild->sibling->sibling->sibling->sibling->sibling

}

int main(){
    return 0;
}