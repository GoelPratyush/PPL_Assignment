#ifndef TRAVERSETREE_H
#define TRAVERSETREE_H

#include "parsetree.h"
#include "typeExpressionTable.h"

void expandTable(typeExpressionTable *t);
void addDimensionRectArray(TypeExpression *template, TreeNode* node);
void addJaggedLimitDim(TypeExpression *template, TreeNode *node);
TypeExpression *addTypeExpression(TreeNode *node, char *varName);
void declarationStatemets(TreeNode* decStatement, typeExpressionTable *t);
void printTypeExpressionTable(typeExpressionTable *t);
void traverseParseTree(TreeNode* head, int ifPrint);

#endif