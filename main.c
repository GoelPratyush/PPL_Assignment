#include <stdio.h>

#include "globals.h"
#include "grammar.h"

int main() {
  // Populates global array of linked lists grammar.
  readGrammar("grammar.txt");

  printGrammar();
}
