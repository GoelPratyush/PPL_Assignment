// Contains declarations required by several files.

#define RULE_COUNT 58         // Number of production rules in the grammar.
#define MAX_LINE_LENGTH 200   // Maximum number of characters in a line in grammar.txt.

typedef struct node Node;

// Symbol is either a terminal (string) or non-terminal (string).
// Convention is:
//  Terminals in all uppercase
//  Non-terminals withing angle brackets
typedef union symbol {
  char* terminal;
  char* nonTerminal;
} Symbol;

typedef struct node {
  int symbolTag;    // If 0, union contains terminal, else contains non-terminal
  Symbol* symbol;   // Union containing terminal/non-terminal
  Node* next;       // Pointer to next node in the linked list
} Node;

// Array of head node pointers, global variable accessible to all files
/* Keeping grammar array as a global variable. Statically allocating because
  we know the number of rules in grammar.txt.
  Also, we need a separate file to keep this global variable. I tried keeping it
  as part of grammar.h, but that led to a circular dependency between grammar.c
  and string_utils.c as:
  * grammar.c needs string_utils.h for string related stuff and reading
    grammar.txt.
  * string_utils.c would need array grammar defined in grammar.h.
  Hence keeping array grammar separate.
*/
Node* grammar[RULE_COUNT];
