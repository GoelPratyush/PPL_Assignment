#ifndef TYPE_EXPRESSION_TABLE_H
#define TYPE_EXPRESSION_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "globals.h"

typedef enum rectangulararraytype RectangularArrayType;
typedef enum errorcode ErrorCode;
typedef enum datatype DataType;
typedef struct typeexpression TypeExpression;
typedef union uniontype UnionType;
typedef struct jag JaggedArray;
typedef struct arr Array;
typedef struct prim Primitive;
typedef struct error Error;
typedef struct typeexpressiontable typeExpressionTable;

typedef enum rectangulararraytype {
    static_,
    dynamic,
    notApplicable
} RectangularArrayType; //Question requirement if it is static or dymanic or none

typedef enum errorcode {
    improperLimits, // Upper limit is less than lower limit
    inappropriateDimension, // For eg R1 [ 105 ] : size 4 : values { 20 21 33 ; 102 ; 35 ; 54 }
    sizeMismatch, //R1 [ 5 ] : size 2 : values { 12 10 100 ; 76 15 8 54 432 ; 29 09 76 11; 67 27 80 }
    limitsUndeclared  // If we have a variable as limit and it is not present in expressionTable then this error
} ErrorCode;

typedef enum datatype {
    boolean,
    integer,
    real
} DataType; //Datatype for each variable

// FOR TABLE YOU CAN MAKE IT AS AN ARRAY BUT THE PURPOSE OF ARRAY WAS TO CREATE SOME KIND OF HASH TABLE TO GET VARIABLES IN O(1) COMPLEXITY
// OR WE CAN HAVE A LINKEDLIST IMPLEMENTATION THAT DECISION IS UPTO YOU
// WE CAN EXPECT A CODE FILE OF 1000 LINE NUMBERS
typedef struct typeexpression {
    char lexeme[MAX_LEXEME_LEN]; //Storing the variables
    int tag; //0 for primitive datatype, 1 for rectangular array, 2 for jagged array. It acts as tag value.
    RectangularArrayType arrayType; //This is of type as enum as it can have only 3 values if it is rectangular then find out if it is static or dynamic. If it is not a rectangular array then not_applicable
    UnionType* unionType; // Union type field 4 carrying information about primitive, rectangular array and jagged array.
    Error* error;
} TypeExpression;

typedef union uniontype{
    Primitive* primitive;
    Array* array;
    JaggedArray* jaggedArray;
} UnionType; //Variable type primitive, rectangular array or jagged array

typedef struct jag {
    int lowerLimit;
    int upperLimit;
    int dimension;
    // For 2D Jagged array store all the values in one column and the second column will remain 1 as the ROWS will be same as COLUMNS
    // For 3D store the size of rows and columns
    // COLUMNS {1;2;3;4} column size is 4 and row size is 1 for each row
    // ROWS {1 2 3; 1 2; 1} column size is 3 and row size is 3 2 1 respectively for each column
    DataType dataType;
	int* size[];
} JaggedArray;

//NOT SURE. YET TO VERIFY
typedef struct arr {
    int dimension;
    DataType dataType;
    int *limits[2]; // 2D array to store the lower and upper limit for each dimension
} Array;

typedef struct prim {
    DataType dataType;
} Primitive;

typedef struct error {
    bool check; //If error then true else false
    ErrorCode errCode; // What type of error
} Error;

void printTypeExpression(TypeExpression* typeExpr);

void initializeSizeofJaggedArray(JaggedArray* jaggedArray); // Allocate the heap memory given the dimensions and limits

void deallocateError(Error* error); // avoid memory leaks

void deallocateJaggedArray(JaggedArray* jaggedArray); //To avoid memory leaks

void deallocateArray(Array* array);

void deallocatePrimitive(Primitive* primitive);

void deallocateUnionType(UnionType* unionType, int tag); // Avoid memory leaks

void deallocateTypeExpression(TypeExpression* typeExpression);

typedef struct typeexpressiontable {
    int varNum;
    TypeExpression *table;
} typeExpressionTable;

#endif
