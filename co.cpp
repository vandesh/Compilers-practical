/* My attempt at Code Optimization - ^Vandesh^ 

   Warning : This program is not optimized for space/time complexity.   
   Written for GCC - Please make appropriate changes if working in TCC.
*/


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>
using namespace std;

struct node   // Data structure for storing DAG
{
int id; //Unique id for table maintanance
char data[5];  // Value in node 
char label[10][10]; // to store multiple Labels associated with a node 
int nol; //Number of labels
node *left,*right; //Left and Right Pointers of node
}*dagtable[20]; // Table containing entry for nodes in DAG

struct quad  //Data structure for storing quadraples
{
char op[2];  
char arg1[5];
char arg2[5];
char result[5];
}table[20],finaltable[20]; //Table of quadraples

int noq=0; //no. of quadraples in input
int non=0; //no. of nodes in DAG table
int noq1=0; //no. of quadraples in output

node* newnode()  //To initialize and create a new node
{
node *temp;
temp=new node;
temp->id=non;
temp->left=NULL;
temp->right=NULL;
strcpy(temp->data,"");
temp->nol=0;
return temp;
}

int searchindag(char testdata[5]) // Searches in lables present in DAG
{
for(int i=0;i<non;++i) //Loop to traverse all nodes in DAG
 {
  for(int j=0;j<dagtable[i]->nol;++j) //Loop to traverse labels of each node 
  if(strcmp(testdata,dagtable[i]->label[j])==0)
  return dagtable[i]->id;  
 }
return -1;
}

int searchifequal(char p[2],char l[5],char r[5]) //Searches for common subexpressions
{
for(int i=0;i<non;++i)
 if(strcmp(p,dagtable[i]->data)==0)
  if(strcmp(l,(dagtable[i]->left)->label[(dagtable[i]->left)->nol-1])==0 && strcmp(r,(dagtable[i]->right)->label[(dagtable[i]->right)->nol-1])==0) 
  return i;
return -1; 
}

void generatedag() //generates DAG for the given Quad table
{
node *parent,*lchild,*rchild;
int r1,r2,r3,r4,flag1=0,flag2=0;
for(int i=0;i<noq;++i)
{

 r3=searchifequal(table[i].op,table[i].arg1,table[i].arg2);  // Elimination of Common Sub-expression
 if(r3!=-1)
 {
  strcpy(dagtable[r3]->label[dagtable[r3]->nol++],table[i].result);
  continue;
 }
 
 r1=searchindag(table[i].arg1);   // For copy propogation

 if(strcmp(table[i].arg2,"-")==0) // Case for "only 1 argument is present"
 {
 rchild=NULL;
 if(r1!=-1)
 {
  strcpy(dagtable[r1]->label[dagtable[r1]->nol++],table[i].result);
  continue;
 }
 else
 {
  r4=searchindag(table[i].result); //Case for when it hasn't been added yet
  if(r4==-1) //Both result and arg1 are not present
  {
   parent = newnode();
   strcpy(parent->label[parent->nol++],table[i].result);
   strcpy(parent->label[parent->nol++],table[i].arg1);
   
   dagtable[non++]=parent;
   continue;
  }
  else
  {
   strcpy(dagtable[r4]->label[dagtable[r4]->nol++],table[i].arg1);
   continue;
  } 
 }
 flag1=1;  // Flag to check if Rchild is NULL
 }
 
 if(!flag1)
 {
 r2=searchindag(table[i].arg2);
 flag1=0;
 }
   
 if(flag2) // Flag to check if further processing is necessary
 {
  flag2=0;
  continue; 
 } 

 if(r1==-1) // arg1 not found in labels
 {
  lchild = newnode();
  strcpy(lchild->label[lchild->nol++],table[i].arg1);
  dagtable[non++]=lchild; 
 }
 else
 {
  lchild = dagtable[r1];
 }
 if(r2==-1) //arg2 not found in labels
 {
  rchild = newnode();
  strcpy(rchild->label[rchild->nol++],table[i].arg2);
  dagtable[non++]=rchild;
 }
 else
 {
  rchild = dagtable[r2];
 }

 parent = newnode();
 strcpy(parent->data,table[i].op);
 parent->left=lchild;
 parent->right=rchild;
 strcpy(parent->label[parent->nol++],table[i].result);
 dagtable[non++]=parent;
 ////////////////////////////////////////////////////////////////////////
 
  
}


}

void quadfromdag() //Which people call antidag ;) LOL Generates quadraples back from DAG
{

for(int i=0;i<non;++i)
{
 if(strcmp(dagtable[i]->data,"")==0) // Only take nodes with data field containing operator
  continue;
 strcpy(finaltable[noq1].op,dagtable[i]->data); 
 strcpy( finaltable[noq1].arg1 , (dagtable[i]->left)->label[(dagtable[i]->left)->nol-1]); 
 if(dagtable[i]->right!=NULL)
 strcpy(finaltable[noq1].arg2,(dagtable[i]->right)->label[(dagtable[i]->right)->nol-1]);
 else
 strcpy(finaltable[noq1].arg2,"-");
 strcpy(finaltable[noq1++].result,dagtable[i]->label[dagtable[i]->nol-1]);
}

}

void parseip() // Parse input from input file into Quad table
{
fstream file;
char temp[5];
int count=0;
file.open("ip.txt",ios::in);
file>>temp;
while(!file.eof())
 {
  strcpy(table[noq].op,temp);
  
  file>>temp;
  strcpy(table[noq].arg1,temp);
  
  file>>temp;
  strcpy(table[noq].arg2,temp);
  
  file>>temp;
  strcpy(table[noq++].result,temp);
  
  file>>temp;
 } 
	
file.close();
}

void printquadtable(quad table3[20],int noq3) // Self Explanatory
{
cout<<endl;
for(int i=0;i<noq3;++i)
cout<<table3[i].op<<"\t"<<table3[i].arg1<<"\t"<<table3[i].arg2<<"\t"<<table3[i].result<<endl;
}

int main()
{
parseip();
printquadtable(table,noq);

generatedag();
quadfromdag();

printquadtable(finaltable,noq1);

return 0;
}
