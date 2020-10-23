#include <stdio.h>
#include "grammar.h"

int MAX_SYMBOL_SIZE; // Stores the length of the longest symbol
// String array of all teriminals and non terminals with the same mapping as that in the defined enum
char *terminal_map[] = {"TERM1", "TERM2"}; 
char *non_terminal_map[] = {"nonterm1", "nonterm2"};
int num_nonterm; // Stores the number of non-terminals in grammar defined
int num_term; // Stores the number of terminals in grammar defined

//Initialization Functions
Grammar* initGrammar(){
    Grammar *g = (Grammar *)malloc(sizeof(Grammar));
    g->no_of_rules = 0;
    g->rules = NULL;
    return g;
};
Rules* initRules(){
    Rules* rules = (Rules*)malloc(sizeof(Rules));
    rules->prods = 0;
    rules->prod_rule = NULL;
    return rules;
}
prodRules* initProdRule(){
    prodRules* newProdRule = (prodRules *)malloc(sizeof(prodRules));
    newProdRule->head = NULL;
    newProdRule->next = NULL;
    return newProdRule;
}
Node* initNode(){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->type.terminal = -1;
    newNode->type_tag = -1;
    newNode->next = NULL;
    return newNode;
}

Grammar* readGrammar(char* file_path){
    Grammar *g = initGrammar();
    //Get number of lines
    int num_of_lines;

    g->no_of_rules = num_of_lines;
    g->rules = (Rules **)malloc(sizeof(Rules*)*num_of_lines);

    FILE* input = fopen(file_path, "r");

    char str[100] = "";
    while(1){
        fscanf(input, "%s\n", str); // Extract each line of grammar.txt and store in str
        if(str[0] == EOF)
            return g;
        
        //extract non-terminal of the rule and store in lhs_non_term
        int idx = 0, lhs_idx = 0;
        char *lhs_non_term = (char*)malloc(sizeof(char)*MAX_SYMBOL_SIZE);
        
        while(str[idx]!='<') // Going to the beginning of lhs non term
            idx++;
        while(str[idx]!='>') // Extracting characters for lhs non term
            lhs_non_term[lhs_idx++] = str[idx++];
        lhs_non_term[lhs_idx] = '\0'; // Specifying end of non term string

        nonTerminal non_term = find(lhs_non_term, 1); // Finds the enum value corresponding to the lhs non terminal
        g->rules[non_term] = buildRules(str);
    }
}

Rules* buildRules(char *rules_str){
    Rules *new_rule = initRules();
    prodRules *curr_prod_rule = NULL; // Dummy pointer used to point to the last prod rule in the list to append to

    // Assuming a grammar rule to be defined as:
    // <non_term1> ==> prod_rule1 | prod_rule2 | prod_rule3

    int idx = 0; // index for traversing rules_str
    while(rules_str[idx] != '>') idx++; // Moving ahead of the lhs non-terminal
    while(rules_str[idx] != '>') idx++; // Moving ahead of the arrow symbol to point to first prodrule

    char *prod_rule_str = (char *)malloc(sizeof(char)*100); // Stores a single prod rule for the non_terminal
    int prod_rule_idx = 0; // Index for storing prod rule character in prod_rule_str
    
    do{
        if(rules_str[idx] == '|' || rules_str[idx] == '\0'){
            prod_rule_str[prod_rule_idx] = '\0'; // Defining the end of a prod rule in the string
            new_rule->prods++; // increment the number of prod-rules for non-term

            // If this is the first prod rule
            if(new_rule->prod_rule == NULL){
                new_rule->prod_rule = buildProdRule(prod_rule_str);
                curr_prod_rule = new_rule->prod_rule;
            }
            // If there are prod rules existing in the list
            else{
                curr_prod_rule->next = buildProdRule(prod_rule_str);
                curr_prod_rule = curr_prod_rule->next;
            }
            prod_rule_idx = 0; // Reinitializing prod rule idx to store next prod rule
        }
        else{
            prod_rule_str[prod_rule_idx++] = rules_str[idx++];
        }
    }while(rules_str[idx] != '\0');

    return new_rule;
}

prodRules* buildProdRule(char* prod_rule_str){
    // Assuming a prod rule to be defined as 
    // <nonTerminal> TERMINAL TERMINAL <nonTerminal>
    // non-terms starting with lowercase and terms starting with upper case
    // all terms & non-terms are space separated

    prodRules *new_prod_rule = initProdRule(); 
    Node* curr_node; // Stores pointer to last added node to update node list
    char *symbol = (char*)malloc(sizeof(char)*MAX_SYMBOL_SIZE); // extracts space separated term/non-term which are referred to as symbol
    int term_nonterm; // tag to determine whether symbol is a term or non-term
    int enum_int; // enum value to determine what term/non-term it is
    int idx = 0, symbol_idx = 0; // indices for traversing prod_rule_str & symbol respectively

    do{
        symbol[symbol_idx] = '\0';

        if(prod_rule_str[idx] == ' ' || prod_rule_str == '\0'){
            // Once a symbol is extracted, this is to determine whether symbol is a terminal or not based on if it's enclosed in <>
            if(symbol[0] == '<'){
                term_nonterm = 1; // Specifying that symbol extracted is a non term
                // Removing < > from the ends of the symbol
                symbol++;
                symbol[strlen(symbol)-1] = '\0';
            }
            else
                term_nonterm = 0;
            
            enum_int = find(symbol, term_nonterm); //Finds the enum value from the character maps defined        

            // Similar to what was done for buildRules
            if(new_prod_rule->head == NULL){
                new_prod_rule->head = buildNode(enum_int, term_nonterm);
                curr_node = new_prod_rule->head;
            }
            else{
                curr_node->next = buildNode(enum_int, term_nonterm);
                curr_node = curr_node->next;
            }

            symbol_idx = 0;
            idx++;   
        }
        else{
            symbol[symbol_idx++] = prod_rule_str[idx++];
        }
    }while(prod_rule_str[idx] != '\0');

    return new_prod_rule;
}

Node* buildNode(int enum_int, int term_nonterm){
    Node* new_node = initNode();
    if(term_nonterm)
        new_node->type.non_terminal = enum_int;
    else
        new_node->type.terminal = enum_int;
    
    new_node->type_tag = term_nonterm;
    
    return new_node;
}

// This function is used to find the enum value corresponding to the terminal/non terminal in string format
int find(char* str, int term_nonterm){
    if(term_nonterm){
        for(int i = 0; i<num_nonterm; i++)
            if(strcmp(str, non_terminal_map[i]) == 0)
                return i;
    }
    else{
        for(int i = 0; i<num_term; i++)
            if(strcmp(str, terminal_map[i]) == 0)
                return i;
    }
}

int main(){
    Grammar *g = readGrammar("grammar.txt");

    return 0;
}