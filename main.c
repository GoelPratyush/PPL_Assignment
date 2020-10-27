#include <stdio.h>

#include "globals.h"
#include "grammar.h"
#include "parser.h"
#include "stack.h"
#include "tokenizer.h"

int main() {
	readGrammar("grammar.txt");

	// ---------- Testing functions from grammar.c ----------
	/* printGrammar();

	Token* headToken = NULL;
	headToken = tokeniseSourcecode("test.txt", headToken);

	Token* leftToken = createNewToken("[", -1);
	Token* rightToken = createNewToken("]", -1);
	imputeEpsilonTokens(headToken, leftToken, rightToken);
	printTokenStream(headToken);

	Symbol* searchSymbol = createSymbol(1, "<com>");
	printf("%d\n", searchLHS(searchSymbol, 30));

	deallocateTokenStream(headToken);

	deallocateGrammar();
	*/

	// ---------- Testing function copyNode ----------
	/* Node* copy = copyNode(grammar[0]);
	printNode(grammar[0]);
	printf(" %d", grammar[0] -> symbolTag);
	printf(" %s", (grammar[0] -> symbol) -> nonTerminal);
	printf(" %p", (grammar[0] -> next));
	printf("\n");

	printNode(copy);
	printf(" %d", copy -> symbolTag);
	printf(" %s", (copy -> symbol) -> nonTerminal);
	printf(" %p", (copy -> next));
	printf("\n");

	printf("\n");

	printf(" %p", &(grammar[0] -> symbolTag));
	printf(" %p", &((grammar[0] -> symbol) -> nonTerminal));
	printf(" %p", &(grammar[0] -> next));
	printf("\n");

	printf(" %p", &(copy -> symbolTag));
	printf(" %p", &((copy -> symbol) -> nonTerminal));
	printf(" %p", &(copy -> next));
	printf("\n");

	Node* copyHead = copyList(grammar[0]);
	printList(copyHead);
	*/

	// ---------- Testing copyList and functions from stack.c ----------
	/* Stack* s = createEmptyStack();
	printStack(s); printf("\n");

	pop(s);
	printStack(s); printf("\n");

	push(s, grammar[0]);
	printStack(s); printf("\n");

	push(s, (grammar[0] -> next) -> next);
	printStack(s); printf("\n");

	push(s, grammar[0] -> next);
	printStack(s); printf("\n");

	popn(s, 3);
	printStack(s); printf("\n");

	pushn(s, grammar[0]);
	printStack(s); printf("\n");

	popn(s, 9);

	pushnReverse(s, grammar[0]);
	printStack(s); printf("\n");
	*/

	// ---------- Testing functions from tokenizer.c ----------
	/* readGrammar("grammar.txt");

	for(int i = 0; i < 10; i++) {
		Token* newToken = createNewToken(grammar[i], )
	}
	*/

	Token* headToken = NULL;
	headToken = tokeniseSourcecode("test.txt", headToken);

	Stack* s = createEmptyStack();
	Node* programNode = createNode(1, "<program>");
	push(s, programNode);
	ruleMatch(0, headToken, s);
}
