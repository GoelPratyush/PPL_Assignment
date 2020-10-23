#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammarDef.h"

//Function Declarations

Grammar* initGrammar();
Rules* initRules();
prodRules* initProdRule();
Node* initNode();

Grammar* readGrammar(char* file_path); // Parses the grammar.txt and for each line, calls buildRules fn and extracts the first non-terminal to store to rules
Rules* buildRules(char* rules_str); // For every | it encounters, extracts a rule and calls buildProdRule and adds it to the prodRule list
prodRules* buildProdRule(char* prod_rule_str); // Breaks the prod rule to extract different words. For each word, makes it a node and adds it to next making a list
//void addProdRule(prodRules *prod_rule, Rules *rule);
Node* buildNode(int enum_int, int term_nonterm); // Given type of term or non terminal and it's tag, returns a node
int find(char* str, int term_nonterm); // Returns the enum value of given terminal/non_terminal