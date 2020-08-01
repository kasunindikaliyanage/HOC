%option noyywrap

%top{ 
	
	#pragma warning (disable: 4005)

	#include <iostream>
	#include <cmath>

	using namespace std;

	#include "../headers/parser.h"

	extern int text_len; 

}

NUMB	([0-9]+)|([0-9]*\.[0-9]+)

%%

{NUMB}			{ yylval.val = atof(yytext); return NUM; }
[+*/()-^=]		{ return yytext[0]; }
[\n]			{ return '\n'; }
[ \t]			{ /* empty */ }
"declare"		{ return DECLARE; }
"quit"			{ yyterminate(); }
[a-zA-Z]+		{
					yylval.name = (char*)malloc(strlen(yytext)+1);
					strncpy(yylval.name, yytext, strlen(yytext));
					yylval.name[strlen(yytext)] = '\0';
					return IDENTIFIER;
				}
.				/* nothing, eat up */

