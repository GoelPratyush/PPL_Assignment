// Returns 1 if string is a terminal, else returns 0.
// IMPORTANT: Ensure the string passed to the function is nul-terminated.
int isTerminal(char s[]);

// Returns 1 if string is a non-terminal, else returns 0.
// Including both isTerminal and isNonTerminal to check if input string is
//  neither (i.e., if there is a mistake in grammar.txt).
// IMPORTANT: Ensure the string passed to the function is nul-terminated.
int isNonTerminal(char s[]);

// Takes a line (string) as input, tokenizes the string into symbols and adds
// symbol to linked list in grammar.
void processLine(char line[], char delimiter[], int grammarIndex);
