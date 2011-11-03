%{
#include"y.tab.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void yyerror(char*);
int adflag=0;
%}
A [a-z]
D [0-9]
trig sin|cos|tan
exp sqr|cube
root sqrt
%%
{trig} {if(strcmp(yytext,"sin")==0) yylval.dval=1; else if(strcmp(yytext,"cos")==0) yylval.dval=2; else yylval.dval=3; return TRIG;}
{exp} {if(strcmp(yytext,"sqr")==0) yylval.dval=1; else yylval.dval=2;return EXPR;}
{root} {yylval.dval=1;return ROOT;}
{A}+ {strcpy(yylval.nam,yytext);return NAME;}
{D}+|{D}*"."{D}+ {yylval.dval=atof(yytext);return NUMBER;}
[ \t];
\n return 0;
. return yytext[0];
%%
int yywrap()
{
printf("\n--OK--\n");
return 1;
}
