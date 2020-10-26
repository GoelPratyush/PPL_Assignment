#include <stdio.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"
#include "tokenizer.h"

int main() {
  // Populates global array of linked lists grammar.
  readGrammar("grammar.txt");

  /* printGrammar();

  Token* headToken = NULL;
  headToken = tokeniseSourcecode("sourcecode.txt", headToken);
  printTokenStream(headToken);

  Symbol* searchSymbol = createSymbol(1, "<com>");
  printf("%d\n", searchLHS(searchSymbol, 30));

  deallocateTokenStream(headToken);

  deallocateGrammar();
  */

  Stack* s = createEmptyStack();
  printStack(s); printf("\n");

  pop(s);
  printStack(s); printf("\n");

  readGrammar("sourcecode.txt");

  push(s, grammar[0]);
  printStack(s); printf("\n");
  push(s, grammar[1]);
  printStack(s); printf("\n");

  popn(s, 3);
  printStack(s); printf("\n");
}
