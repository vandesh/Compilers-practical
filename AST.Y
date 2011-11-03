%{
#include<stdio.h>
struct node
{
char data;
struct node *left, *right;
};
struct node* gen_node(char);
void assignlr(struct node*,struct node*,struct node*);
%}
%union{
struct node *temp;
char symb;
char nam[20];
}
%token <nam> NAME
%token <symb> NUMBER
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%type <temp> exp
%%
stmt:NAME '=' exp {/*printf("\n%s=%f\n",$1,$3);*/}
    |exp {/*printf("%f\n",$1);*/}
    ;
exp:'(' exp ')' {$$=$2;}
   |exp '+' exp {$$=gen_node('+');assignlr($$,$1,$3);display($$);printf("\n");}
   |exp '-' exp {$$=gen_node('-');assignlr($$,$1,$3);display($$);printf("\n");}
   |exp '*' exp {$$=gen_node('*');assignlr($$,$1,$3);display($$);printf("\n");}
   |exp '/' exp {$$=gen_node('/');assignlr($$,$1,$3);display($$);printf("\n");}
   |NUMBER {$$=gen_node($1);printf("\n");}
   ;
%%
void display(struct node *pnode)
{
printf("Node->\t%c\t",pnode->data);
if(pnode->left==NULL)
{
printf("\tNULL	NULL");
return;
}
else
{
printf("\n");
printf("Left->");
display(pnode->left);
printf("\n");
printf("Right->");
display(pnode->right);
}
}
void assignlr(struct node *parent,struct node *lnode,struct node *rnode)
{
parent->left=lnode;
parent->right=rnode;
}

struct node* gen_node(char t)
{
struct node *temp_node;
temp_node=(struct node*)malloc(sizeof(struct node));
temp_node->data=t;
temp_node->left=NULL;
temp_node->right=NULL;
return temp_node;
}
void yyerror(char *error)
{
printf("%s\n",error);
}
void main()
{
yyparse();
}
