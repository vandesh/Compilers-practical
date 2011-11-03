%{
#include"y_tab.h"
#include<math.h>
#include<stdlib.h>
#include<string.h>
void yyerror(char*);
%}
A [a-z]
D [0-9]
%%
{A}+ {strcpy(yylval.nam,yytext);return NAME;}
{D}+ {yylval.symb=yytext[0];return NUMBER;}
[ \t];
\n return 0;
. return yytext[0];
%%
int yywrap()
{
printf("\n--OK--\n");
return 1;
}
