#include "traversetree.h"

typeExpressionTable *initTypeExpressionTable(){
    typeExpressionTable *newTable = (typeExpressionTable*)malloc(sizeof(typeExpressionTable));
    //newTable->table = NULL;
    newTable->varNum = 0;
    return newTable;
}

// Function expands the table by 10 units
void expandTable(typeExpressionTable *t){
    if(t->varNum == 0){
        t->table = (TypeExpression**)malloc(sizeof(TypeExpression*)*10);
        //for(int i = 0; i<10; i++)
        //    t->table[i] = (TypeExpression*)malloc(sizeof(TypeExpression));
    }
    else{
        int initSize = sizeof(TypeExpression*)*t->varNum;
        t->table = (TypeExpression**) realloc(t->table, initSize+sizeof(TypeExpression*)*10);
        //for(int i = t->varNum; i<t->varNum+10; i++)
        //    t->table[i] = (TypeExpression*)malloc(sizeof(TypeExpression));
    }
}

//This funciton is just to add dimension details for rectangular Arrays in a recursive format
void addDimensionRectArray(TypeExpression* template, TreeNode* node){
    node = node->leftChild;
    int num = template->unionType->array->dimension;

    if(template->unionType->array->dimension == 0){
        template->unionType->array->limits[0] = (int *)malloc(sizeof(int));
        template->unionType->array->limits[1] = (int *)malloc(sizeof(int));
    }
    else{
        template->unionType->array->limits[0] = (int *)realloc(template->unionType->array->limits[0], sizeof(int)*(num+1));
        template->unionType->array->limits[1] = (int *)realloc(template->unionType->array->limits[1], sizeof(int)*(num+1));
    }

    template->unionType->array->dimension++;

    // Storing the limits
    // *********** Check limits mismatch for errors **************
    // if conditions to check if passed limit is <var> or NUM. If <var> store -1 as limit and make array dynamic

    if(node->sibling->leftChild->symbolTag == 0)
        template->unionType->array->limits[0][num] = node->sibling->leftChild->treeNodeType->terminal->token->instInt;
    else{
        template->unionType->array->limits[0][num] = -1;
        template->arrayType = dynamic;
    }
    if(node->sibling->sibling->sibling->leftChild->symbolTag == 0)
        template->unionType->array->limits[1][num] = node->sibling->sibling->sibling->leftChild->treeNodeType->terminal->token->instInt;
    else{
        template->unionType->array->limits[1][num] = -1;
        template->arrayType = dynamic;
    }

    // Hard coding, checking if <dimension> has <dimension> as a sibling in 5th place, if it exists, it is <dimension> else it's NULL
    if(node->sibling->sibling->sibling->sibling->sibling)
        addDimensionRectArray(template, node->sibling->sibling->sibling->sibling->sibling);
}

//The function just adds limits of first dimension and the count of dimensions of JaggedArray
void addJaggedLimitDim(TypeExpression *template, TreeNode *node){
    //Node is initially at JAGGED after coming down from <jagged_array1>
    //*********** Error for unacceptable limits ***************

    node = node->sibling->sibling->sibling; //Moved node to <limit2>
    
    template->unionType->jaggedArray->lowerLimit = node->leftChild->treeNodeType->terminal->token->instInt;
    node = node->sibling->sibling; //Moved node to <limit2>
    
    template->unionType->jaggedArray->upperLimit = node->leftChild->treeNodeType->terminal->token->instInt;

    // If <dim> expands to <dim2>(non term), then it's 2 dimensional else it expands to SQO(term)
    if(node->sibling->sibling->leftChild->symbolTag == 0)
        //************ Error for declaring more than 3 dimensions? **************
        template->unionType->jaggedArray->dimension = 3;
    else
        template->unionType->jaggedArray->dimension = 2;
}

void addJaggedSize(TypeExpression *template, TreeNode *node, int rows){
    //node at <jagged_array2>

    for(int i = 0; i<rows; i++){
        TreeNode *tempNode = node->leftChild; // tempNode on R1
        TreeNode *colNode = NULL;
        
        tempNode = tempNode->sibling->sibling->sibling->sibling->sibling->sibling; // tempNode on <size>
        
        int cols = tempNode->leftChild->treeNodeType->terminal->token->instInt;
        template->unionType->jaggedArray->colSize[i] = cols;
        template->unionType->jaggedArray->depth[i] = (int*)malloc(sizeof(int)*cols);

        tempNode = tempNode->sibling->sibling->sibling->sibling->leftChild; // tempNode at <column>
        for(int j = 0; j<cols; j++){
            int depth = 1;
            colNode = tempNode->leftChild; //colNode at NUM

            do{
                colNode = colNode->sibling;
                if(colNode){
                    colNode = colNode->leftChild;
                    depth++;
                }
            }while(colNode);

            template->unionType->jaggedArray->depth[i][j] = depth;
            if(tempNode->sibling)
                tempNode = tempNode->sibling->sibling->leftChild; // tempNode goes to next <column>
        }
        //***************** Error report if not enough rows/ more rows defined ***************
        if(node->sibling)
            node = node->sibling->leftChild;
    }
}

// Creates a typeExpression of a variable.
// node points to the first sibling of COLON
TypeExpression *addTypeExpression(TreeNode *node, char *varName){
    TypeExpression *template = (TypeExpression*)malloc(sizeof(TypeExpression));
    template->error = (Error *)malloc(sizeof(Error));
    template->error->check = false;
    template->error->errCode = 0;
    template->unionType = (UnionType *)malloc(sizeof(UnionType));
    strcpy(template->lexeme, varName);

    if(strcmp(node->symbol->nonTerminal, "<jagged_array1>") == 0){
        //Node is at <jagged_array1>
        
        template->tag = 2;
        template->unionType->jaggedArray = (JaggedArray *)malloc(sizeof(JaggedArray));
        template->arrayType = notApplicable;

        if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "INT") == 0)
            template->unionType->jaggedArray->dataType = integer;
        else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "BOOL") == 0)
            template->unionType->jaggedArray->dataType = boolean;
        else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "REAL") == 0)
            template->unionType->jaggedArray->dataType = real;
        else{
            //********************** For the case we have none of INT BOOL REAL in our declaration statement, record as error? ****************
        }   

        addJaggedLimitDim(template, node->leftChild);

        int rows = template->unionType->jaggedArray->upperLimit - template->unionType->jaggedArray->lowerLimit + 1;
        template->unionType->jaggedArray->depth = (int **)malloc(sizeof(int *)*rows);
        template->unionType->jaggedArray->colSize = (int *)malloc(sizeof(int)*rows);
        
        addJaggedSize(template, node->sibling->sibling->sibling->sibling->leftChild, rows); // Passing <jagged_array2>
    }
    else{
        node = node->leftChild;

        // If primitive data type, <type> has no sibling
        if(node->sibling){
            // For the case of rectangular array
            // node is at <array>
            template->tag = 1;
            template->unionType->array = (Array *)malloc(sizeof(Array));
            template->arrayType = static_; // Initializing to static, if an identifier is encountered while populating dimension, will be changed to dynamic
            template->unionType->array->dimension = 0;

            // Hard coding for type extraction
            // node->sibling->sibling is <type> node
            if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "INT") == 0)
                template->unionType->array->dataType = integer;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "BOOL") == 0)
                template->unionType->array->dataType = boolean;
            else if(strcmp(node->sibling->sibling->leftChild->symbol->terminal, "REAL") == 0)
                template->unionType->array->dataType = real;
            else{
                //********************** For the case we have none of INT BOOL REAL in our declaration statement, record as error? *****************
            }

            node = node->leftChild->sibling; //Node is now at <dimension>
            
            addDimensionRectArray(template, node); 
        }
        else{
            // For the case of primitive data type
            // node is at <type>
            template->tag = 0;
            template->arrayType = notApplicable;
            template->unionType->primitive = (Primitive *)malloc(sizeof(Primitive));

            if(strcmp(node->leftChild->symbol->terminal, "INT") == 0)
                template->unionType->primitive->dataType = integer;
            else if(strcmp(node->leftChild->symbol->terminal, "BOOL") == 0)
                template->unionType->primitive->dataType = boolean;
            else if(strcmp(node->leftChild->symbol->terminal, "REAL") == 0)
                template->unionType->primitive->dataType = real;
            else{
                //********************** For the case we have none of INT BOOL REAL in our declaration statement, record as error? ******************
            }
        }
    }

    return template;
}

// This function starts at <stmt> node of the parse tree and recursively calls itself for each <stmt> node of the parse tree and populates the typeExpressionTable for each of <stmt>
void declarationStatemets(TreeNode* decStatement, typeExpressionTable *t){
    // Handling DECLARE LIST and DECLARE separately
    // If DECLARE LIST then the first sibling of DECLARE will be LIST that is a terminal, else it will be <var> which is a non_terminal
    
    if(decStatement->leftChild->sibling->symbolTag == 1){
        // For the case of a single variable declared
        t->varNum++;
        //**printf("t->varNum = %d\n", t->varNum);
        if(t->varNum%10 == 0)
            expandTable(t);
        // Passing the first node after COLON and variable name from left child of <var>
        t->table[t->varNum-1] = addTypeExpression(decStatement->leftChild->sibling->sibling->sibling, decStatement->leftChild->sibling->leftChild->treeNodeType->terminal->token->lexeme);
    }
    else{
        
        // For the case of list of variables declared
        // Call addTypeExpression() for all variables of list, , call expandTypeExpressionTable as per need
        TreeNode *node = decStatement->leftChild; // node is at DECLARE
        node = node->sibling->sibling->sibling->sibling->leftChild; // node is at <var> 
        do{
            t->varNum++;
            if(t->varNum%10 == 0)
                expandTable(t);
            // Passing the first node after COLON and variable name of each variable
            t->table[t->varNum-1] = addTypeExpression(decStatement->leftChild->sibling->sibling->sibling->sibling->sibling->sibling, node->leftChild->treeNodeType->terminal->token->lexeme);

            node = node->sibling;
            if(node)
                node = node->leftChild;
        }while(node);
        
    }

    // If <stmt> has a sibling, it has to be <declaration_stmt>, hence recursively call this function for all <stmt> nodes
    if(decStatement->sibling)
        declarationStatemets(decStatement->sibling->leftChild, t);
}

void printTypeExpression(TypeExpression *te){
    printf("<type=");
    DataType tempDataType;
    if(te->tag == 0){
        printf("primitive, ");
        tempDataType = te->unionType->primitive->dataType;
    }
    else if(te->tag == 1){
        int dim = te->unionType->array->dimension;
        printf("rectangularArray, dimensions=%d, ", dim);
        for(int i = 0; i<dim; i++){
            printf("range_R%d=(%d,%d), ", i+1, te->unionType->array->limits[0][i], te->unionType->array->limits[1][i]);
        }
        tempDataType = te->unionType->array->dataType;
    }
    else{
        int dim = te->unionType->jaggedArray->dimension;
        int rows = te->unionType->jaggedArray->upperLimit - te->unionType->jaggedArray->lowerLimit + 1;
        tempDataType = te->unionType->jaggedArray->dataType;
        printf("jaggedArray, dimensions=%d, range_R1=(%d,%d), range_R2=(",dim, te->unionType->jaggedArray->lowerLimit, te->unionType->jaggedArray->upperLimit);
        if(dim == 2){
            printf("%d", te->unionType->jaggedArray->colSize[0]);
            for(int i = 1; i<rows; i++)
                printf(",%d", te->unionType->jaggedArray->colSize[i]);
        }
        else{
            int col = te->unionType->jaggedArray->colSize[0];
            printf("%d[%d",col,te->unionType->jaggedArray->depth[0][0]);
            for(int i = 1; i<col; i++)
                printf(",%d", te->unionType->jaggedArray->depth[0][i]);
            printf("]");
            for(int i = 1; i<rows; i++){
                col = te->unionType->jaggedArray->colSize[i];
                printf(",%d[%d",col, te->unionType->jaggedArray->depth[i][0]);
                for(int j = 0; j<col; j++)
                    printf(",%d", te->unionType->jaggedArray->depth[i][j]);
                printf("]");
            }
        }
        printf("), ");
    }
    printf("basicElementType=");
    if(tempDataType==boolean)   
        printf("boolean>");
    else if(tempDataType==integer)
        printf("integer>");
    else
        printf("real>");
}

void printTypeExpressionTable(typeExpressionTable *t){

    for(int i = 0; i<t->varNum; i++){
        UnionType *unionPointer = t->table[i]->unionType;
        int tempTag = t->table[i]->tag;

        
        printf("%-20s", t->table[i]->lexeme);
        
        if(tempTag == 0)
            printf("%-14s","Primitive");
        else if(tempTag == 1)
            printf("%-14s","Rectangular");
        else if(tempTag == 2)
            printf("%-14s","Jagged Array");

        if(t->table[i]->arrayType == static_)
            printf("%-16s","Static");
        else if(t->table[i]->arrayType == dynamic)
            printf("%-16s","Dynamic");
        else if(t->table[i]->arrayType == notApplicable)
            printf("%-16s","Not Applicable");
        /*
        if(tempTag == 0)
            printf("Field 4 - %d\n", unionPointer->primitive->dataType);
        else if(tempTag == 1){
            printf("Field 4 - Dimension = %d\n", unionPointer->array->dimension);
            printf("Field 4 - dataType = %d\n", unionPointer->array->dataType);
            for(int i = 0; i<unionPointer->array->dimension; i++)
                printf("Field 4 - Limit i = %d, ll = %d, ul = %d\n", i, unionPointer->array->limits[0][i], unionPointer->array->limits[1][i]);
        }
        else if(tempTag == 2){
            printf("Field 4 - Lower limit =  %d\n", unionPointer->jaggedArray->lowerLimit);
            printf("Field 4 - Upper limit =  %d\n", unionPointer->jaggedArray->upperLimit);
            printf("Field 4 - Dimension = %d\n", unionPointer->jaggedArray->dimension);
            printf("Field 4 - dataType = %d\n", unionPointer->jaggedArray->dataType);
            printf("Field 4 - Depths : \n");
            int rows = unionPointer->jaggedArray->upperLimit - unionPointer->jaggedArray->lowerLimit + 1;
            for(int i = 0; i<rows; i++){
                for(int j = 0; j<unionPointer->jaggedArray->colSize[i]; j++){
                    printf("%d ", unionPointer->jaggedArray->depth[i][j]);
                }
                printf("\n");
            }
        }
        */
        printTypeExpression(t->table[i]);
        printf("\n");
    }
}

void deallocateTypeExpression(TypeExpression* te) {
    if (te == NULL){
        return;
    }

    if(te->tag == 0)
        free(te->unionType->primitive);
    if(te->tag == 1){
        free(te->unionType->array->limits[0]);
        free(te->unionType->array->limits[1]);
        free(te->unionType->array);
    }
    if(te->tag == 2){
        int rows = te->unionType->jaggedArray->upperLimit - te->unionType->jaggedArray->lowerLimit + 1;
        for(int i = 0; i<rows; i++)
            free(te->unionType->jaggedArray->depth[i]);
        free(te->unionType->jaggedArray->depth);
        free(te->unionType->jaggedArray->colSize);
        free(te->unionType->jaggedArray);
    }
        
    free(te->unionType);
    free(te);
}

void deallocateTypeExpressionTable(typeExpressionTable *t){
    for(int i = 0; i<t->varNum; i++)
        deallocateTypeExpression(t->table[i]);
    free(t->table);
    free(t);
}

void traverseParseTree(TreeNode* head, int ifPrint){
    typeExpressionTable *t = initTypeExpressionTable();
    expandTable(t);

    // head is at <program>
    declarationStatemets(head->leftChild->sibling->sibling->sibling->sibling->leftChild, t); // Passing node pointing to <stmt>
    printf("Type expression Table created successfully\n");
    
    if(ifPrint)
        printTypeExpressionTable(t);

    deallocateTypeExpressionTable(t);
    //printf("Dallocation done\n");
}