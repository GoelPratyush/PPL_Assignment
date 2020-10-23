#include <stdio.h>

#include "globals.h"
#include "grammar.h"
#include "token.h"

int main() {
  // Populates global array of linked lists grammar.
  readGrammar("grammar.txt");

  printGrammar();

  Token* headToken = NULL;
  headToken = tokeniseSourcecode("sourcecode.txt", headToken);
  printTokenStream(headToken);

  deallocateTokenStream(headToken);
}
