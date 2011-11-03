%{
#include<math.h>
%}

%union{
double dval;
char nam[20];
}
%token <nam> NAME
%token <dval> NUMBER TRIG EXPR ROOT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%type <dval> exp
%%
stmt:NAME '=' exp {printf("\n%s=%f\n",$1,$3);}
    |exp {printf("%f\n",$1);}
    ;
exp:'(' exp ')' {$$=$2;}
   |exp '+' exp {$$=$1+$3;}
   |exp '-' exp {$$=$1-$3;}
   |exp '*' exp {$$=$1*$3;}
   |exp '/' exp {$$=$1/$3;}
   |TRIG exp {if($1==1) $$=sin((3.1428/180) * $2); else if($1==2) $$=cos($2); else $$=tan($2);}
   |EXPR exp {if($1==1) {$$=$2*$2;} else $$=$2*$2*$2;}
   |ROOT exp {$$=sqrt($2);}
   |NUMBER {$$=$1;}
   ;
%%
void yyerror(char *error)
{
printf("%s\n",error);
}
void main()
{
yyparse();
}
