#ifndef TYPE_EXPRESSION_TABLE_H
#define TYPE_EXPRESSION_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "globals.h"

typedef enum {
    static_,
    dynamic,
    notApplicable
} RectangularArrayType; //Question requirement if it is static or dymanic or none

typedef enum{
    improperLimits, // Upper limit is less than lower limit
    inappropriateDimension, // For eg R1 [ 105 ] : size 4 : values { 20 21 33 ; 102 ; 35 ; 54 }
    sizeMismatch, //R1 [ 5 ] : size 2 : values { 12 10 100 ; 76 15 8 54 432 ; 29 09 76 11; 67 27 80 }
    limitsUndeclared  // If we have a variable as limit and it is not present in expressionTable then this error
} ErrorCode;

typedef enum{
    boolean,
    integer,
    real
} DataType; //Datatype for each variable

// FOR TABLE YOU CAN MAKE IT AS AN ARRAY BUT THE PURPOSE OF ARRAY WAS TO CREATE SOME KIND OF HASH TABLE TO GET VARIABLES IN O(1) COMPLEXITY
// OR WE CAN HAVE A LINKEDLIST IMPLEMENTATION THAT DECISION IS UPTO YOU
// WE CAN EXPECT A CODE FILE OF 1000 LINE NUMBERS
typedef struct {
    char lexeme[MAX_LEXEME_LEN]; //Storing the variables
    int tag; //0 for primitive datatype, 1 for rectangular array, 2 for jagged array. It acts as tag value.
    RectangularArrayType arrayType; //This is of type as enum as it can have only 3 values if it is rectangular then find out if it is static or dynamic. If it is not a rectangular array then not_applicable
    StructType type; // Union type field 4 carrying information about primitive, rectangular array and jagged array.
} TypeExpression;

typedef union{
    Primitive primitive;
    Array array;
    JaggedArray jaggedArray;
} StructType; //Variable type primitive, rectangular array or jagged array

typedef struct{
    int lowerLimit;
    int upperLimit;
    int dimension;
    // For 2D Jagged array store all the values in one column and the second column will remain 1 as the ROWS will be same as COLUMNS
    // For 3D store the size of rows and columns
    // COLUMNS {1;2;3;4} column size is 4 and row size is 1 for each row
    // ROWS {1 2 3; 1 2; 1} column size is 3 and row size is 3 2 1 respectively for each column
    int* size[];
    DataType dataType;
    Error error; // Error while declaration as that time we are populating it.
} JaggedArray;

//NOT SURE. YET TO VERIFY
typedef struct{
    int dimension;
    DataType dataType;
    int *limits[2]; // 2D array to store the lower and upper limit for each dimension
    ErrorCode errCode;
} Array;

typedef struct{
    DataType dataType;
} Primitive;

typedef struct{
    bool check; //If error then true else false
    ErrorCode errCode; // What type of error
} Error;

void InitializeSizeofJaggedArray(JaggedArray* jaggedArray); // Allocate the heap memory given the dimensions and limits

typedef struct{
    int varNum;
    TypeExpression *table;
} typeExpressionTable;

#endif
