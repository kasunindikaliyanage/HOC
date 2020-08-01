%defines "parser.h"

%{
	#include <cmath>
	#include <cstdio>
	#include <iostream>
	#include <string>

	#include "../headers/symbol_management.h"

	#pragma warning (disable: 4005)
	
	// this function will be generated
	// by flex
	extern int yylex(); // lexical analyzer
	 
	 // we have to code this function
	extern void yyerror(const char*);

	using namespace std;
%}

%union {
double     val;		/* For returning numbers.                   */
char*	   name;			/* For returning symbol-table pointers      */
}

%token <val> NUM
%token <name> DECLARE
%token <name> IDENTIFIER   /* Variable and Function            */
%type  <val>  exp

%left '-' '+'
%left '*' '/'
%right '^'    /* exponentiation        */
%left NEG     /* negation--unary minus */

%%		/* the grammars here */

input: %empty
	| input line
	;

line: '\n'
	| exp '\n'	{ printf ("\t%.10g\n", $1); return 0; }
	; 

exp: NUM						{ $$ = $1; }
	| IDENTIFIER				{ $$ = get_identifier($1)->value; }
	| DECLARE IDENTIFIER		{ $$ = put_identifier($2)->value; }
	| IDENTIFIER '=' exp		{ $$ = $3; put_value($1,$3); }
	| IDENTIFIER '(' exp ')'	{ $$ = get_identifier($1)->function($3); }
	| exp '+' exp				{ $$ = $1 + $3; }
	| exp '-' exp				{ $$ = $1 - $3; }
	| exp '*' exp				{ $$ = $1 * $3; }
	| exp '/' exp				{ $$ = $1 / $3; }
	| '-' exp %prec NEG			{ $$ = -$2; } 
	| exp '^' exp				{ $$ = pow ($1, $3); }
	| '(' exp ')'				{ $$ = $2; }
	;

%%