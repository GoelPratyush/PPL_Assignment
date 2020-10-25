#include <stdio.h>

#include "globals.h"
#include "grammar.h"
#include "tokenizer.h"
#include "parser.h"

int main() {
  // Populates global array of linked lists grammar.
  readGrammar("grammar.txt");

  printGrammar();

  Token* headToken = NULL;
  headToken = tokeniseSourcecode("sourcecode.txt", headToken);
  printTokenStream(headToken);

  Symbol* searchSymbol = createSymbol(1, "<com>");
  printf("%d\n", searchLHS(searchSymbol, 30));

  deallocateTokenStream(headToken);

  deallocateGrammar();
}
