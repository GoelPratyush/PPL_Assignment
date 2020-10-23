#include <stdio.h>
#include <stdlib.h>

#include "lexerDef.h"

typedef Tokentype Terminal;
typedef enum{nonterm1, nonterm2} nonTerminal;

typedef union symboltype{
    Terminal terminal;
    nonTerminal non_terminal;
}symbolType;

// Each production rule has been implemented as a list of nodes where each node is a terminal or non terminal.
typedef struct node{
    symbolType type; // This is used to store (enum value) what terminal or non terminal the symbol is
    int type_tag; // This is used a tag to specify if the symbol is a terminal or non-terminal

    struct node* next; // Pointer to the next node in the production rule
}Node;

// A non-terminal can have multiple production rules which have been implemented as a list.
// Each production rule points to the next rule for that non-terminal
typedef struct prodList{
    Node* head;
    struct prodList *next; // Points to the next prodRule
}prodRules;

typedef struct rules{
    int prods; // Number of production rules for a non terminal
    prodRules *prod_rule; // Pointer poiinting to the first prod rule
}Rules;

typedef struct grammar{
    int no_of_rules; // Number of rules defined in grammar
    Rules **rules; // Array of all defined non-terminal's prouction rules
}Grammar;
