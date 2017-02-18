#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

void add_history(char* unused) {}
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif


int main(int argc, char**argv) {
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Clisp = mpc_new("clisp");


  mpca_lang(
	  MPCA_LANG_DEFAULT,
	  "number: /-?\\d+(\\.\\d+)?/; \
           operator: /add|\\+/ | /sub|\\-/ | /mul|\\*/ | /div|\\//; \
           expr: <number> | '(' <operator> <expr>+ ')'; \
           clisp: /^/ <operator> <expr>+ /$/;",
	  Number, Operator, Expr, Clisp
	    );

  puts("It is dummy version Clisp.");
  puts("Lispy version 0.1");
  puts("Press Ctrl + C to Exit\n");

  while(1) {
	  char* input = readline("Clisp> ");

	  add_history(input);

	  mpc_result_t result;
	  if (mpc_parse("<stdin>", input, Clisp, &result)) {
		  // On Success Print the AST
		  mpc_ast_print(result.output);
		  mpc_ast_delete(result.output);
	  } else {
		  // Otherewise Print the Error
		  mpc_err_print(result.error);
		  mpc_err_delete(result.error);
	  }

	  free(input);
  }

  // Delete parser
  mpc_cleanup(4, Number, Operator, Expr, Clisp);
  
  return 0;
}

