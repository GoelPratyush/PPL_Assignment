#include "parsetree.h"

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

//This funciton is just to add dimension details for rectangular Arrays in a recursive format
void addDimensionRectArray(TypeExpression* template, TreeNode* node){
    node = node->leftChild;

    if(template->unionType->array->dimension == 0){
        template->unionType.array.limits[0] = (int *)malloc(sizeof(int));
        template->unionType.array.limits[1] = (int *)malloc(sizeof(int));
    }
    else{
        template->unionType.array.limits[0] = (int *)realloc(template->unionType->array->limits[0], sizeof(int)*(num+1));
        template->unionType.array.limits[1] = (int *)realloc(template->unionType->array->limits[0], sizeof(int)*(num+1));
    }

    int num = template->unionType.array.dimension;
    template->unionType.array.dimension++;

    // Storing the limits
    // ***********
    // Check limits mismatch for errors
    // if conditions to check if passed limit is <var> or NUM. If <var> store -1 as limit and make array dynamic
    if(node->sibling->leftChild->symbolTag == 0)
        template->unionType.array.limits[0][num] = node->sibling->leftChild->treeNodeType->terminal->token->instInt;
    else{
        template->unionType.array.limits[0][num] = -1;
        template->arrayType = dynamic;
    }
    if(node->sibling->sibling->sibling->leftChild->symbolTag == 0)
        template->unionType.array.limits[1][num] = node->sibling->sibling->sibling->leftChild->treeNodeType->terminal->token->instInt;
    else{
        template->unionType.array.limits[1][num] = -1;
        template->arrayType = dynamic;
    }

    // Hard coding, checking if <dimension> has <dimension> as a sibling in 5th place, if it exists, it is <dimension> else it's NULL
    if(node->sibling->sibling->sibling->sibling->sibling)
        addDimensionRectArray(template, node->sibling->sibling->sibling->sibling->sibling);
}

// Creates a template typeExpression that can be copied for any number of variables that share the same template
// *node points to the first sibling of COLON
TypeExpression *addTypeExpression(TreeNode *node, char *varName){
    TypeExpression *template = (TypeExpression*)malloc(sizeof(TypeExpression));
    strcpy(template->lexeme, varName);

    if(strcmp(node->symbol->nonTerminal, "<jagged_array1>"){
        //Node is at <jagged_array1>
        template->tag = 2;
        template->arrayType = notApplicable;

        if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "INT") == 0)
            template->unionType.jaggedArray.dataType = integer;
        else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "BOOL") == 0)
            template->unionType.jaggedArray.dataType = boolean;
        else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "REAL") == 0)
            template->unionType.jaggedArray.dataType = real;
        else{
            //**********************
            // For the case we have none of INT BOOL REAL in our declaration statement, record as error?
        }        
    }
    else{
        node = node->leftChild;

        // If primitive data type, <type> has no sibling
        if(node->sibling){
            // For the case of rectangular array
            // node is at <array>
            template->tag = 1;
            template->arrayType = static_; // Initializing to static, if an identifier is encountered while populating dimension, will be changed to dynamic

            // Hard coding for type extraction
            // node->sibling->sibling is <type> node
            if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "INT") == 0)
                template->unionType.array.dataType = integer;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "BOOL") == 0)
                template->unionType.array.dataType = boolean;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "REAL") == 0)
                template->unionType.array.dataType = real;
            else{
                //**********************
                // For the case we have none of INT BOOL REAL in our declaration statement, record as error?
            }

            node = node->leftChild->sibling; //Node is now at <dimension>

            addDimensionRectArray(template, node); 
        }
        else{
            // For the case of primitive data type
            // node is at <type>
            template->tag = 0;
            template->arrayType = notApplicable;

            if(strcmp(node->leftChild->symbol->terminal, "INT") == 0)
                template->unionType.primitive.dataType = integer;
            else if(strcmp(node->leftChild->symbol->terminal, "BOOL") == 0)
                template->unionType.primitive.dataType = boolean;
            else if(strcmp(node->leftChild->symbol->terminal, "REAL") == 0)
                template->unionType.primitive.dataType = real;
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