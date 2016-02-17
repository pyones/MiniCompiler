//////////////////////////
////////Edward Pyon CS 440   Lab 1
/////////////////////////////////






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"  //opensource data structure
#include "tokens.h"

extern int lineno;
extern int counter;
int lookahead;
extern char* val;

void prodList();
void match(int token);
void prodListProduction();
void production();
void productionBody();
void productionRule();
void rule();
void passOne();
void passTwo();
void passThree();
Arraylist getTerminal(char* key, Arraylist updated);
void printfinal();
Boolean contains(Arraylist strList, char* input);



int semiCounter=0;


	

const Boolean objEquals(const Object object_1, const Object object_2)
{
  return (object_1 == object_2);
}

Arraylist stringArray;
Arraylist intArray;
Arraylist finalString;
Arraylist finalInt;

Arraylist p1Int;
Arraylist p1Str;

Arraylist p2Int;
Arraylist p2Str;

Arraylist p3Str;

main(int argc, char**argv) {
	lookahead = yylex();
	stringArray = arraylist_create(objEquals);
	intArray = arraylist_create(objEquals);
	finalString = arraylist_create(objEquals);
	finalInt = arraylist_create(objEquals);
	p1Int = arraylist_create(objEquals);
	p1Str = arraylist_create(objEquals);
	p2Int = arraylist_create(objEquals);
	p2Str = arraylist_create(objEquals);
	p3Str = arraylist_create(objEquals);

	prodList();
	if(lookahead!=0){
		printf("error");
		return 0;
	}	

	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters

	//prints the CFG LL
	r=arraylist_size(finalString);//r is row
	for (i=0;i<r;i++){
		c=arraylist_size(arraylist_get(finalString,i));
		for(j=0;j<c;j++){
			char *str=arraylist_get(arraylist_get(finalString,i),j);
			int *num=arraylist_get(arraylist_get(finalInt,i),j);
			//printf("%s",str);

			if (arraylist_get(arraylist_get(finalInt,i),(j+1))==GOES)
				printf("\n%s ",str);
			else if (num==GOES)
				printf("%s\t\t",str);
			else if (num==OR)
				printf("\n\t%s\t",str);
			else if (num==7)
				printf("");
			else printf("%s ",str);
		}
	}

	printf("\n");
	passOne();
	printf("\n");
	passTwo();
	printf("\n");
	passThree();
	
	printfinal();
}

//////////////////
///Start of the Recursive Descent Parser
/////////////////

void prodList(){
	if(lookahead==NT){
		// printf("%s", val);
		// arraylist_add(stringArray,val);
		// arraylist_add(intArray,lookahead);
		//insert(list, val, lookahead);
		//match(NT); NT is nonterminal
		production(); 
		prodListProduction();
	}
	else if(lookahead==EOLN){
		match(EOLN); production; prodListProduction();
	}
}

void match(int token){
	if(token==lookahead){
		if(lookahead==GOES){
		 	//printf(" %s", val);
		 	arraylist_add(stringArray,val);
			arraylist_add(intArray,lookahead);
		}
		lookahead=yylex();
	}
	else {printf("error1");} //printf(" %s ", val);}
}

void prodListProduction(){
	if(lookahead==NT){
		production(); 
		prodListProduction();
	}
	else if(lookahead==0)
		return;
	else 
		printf("error2");
}

void production(){
	//printf("hello");
	//val=yytext();
	//printf(" %s", val);
	arraylist_add(stringArray,val);
	arraylist_add(intArray,lookahead);
	//strcpy(list[count],str);
	match(NT);
	match(GOES);
	productionBody();
	match(SEMI);
	//printf("\n");
	match(EOLN);	
}


void productionBody(){
	if(lookahead==NT||lookahead==T||lookahead==EOLN){
		if(lookahead==EOLN){
			//strcpy(list[count],"epsilon"); count++;
			//printf(" epsil");
			arraylist_add(stringArray,"Epsilon");
			arraylist_add(intArray,7);
		}
		rule(); productionRule();
	}
	else printf("\nPB");

}

void productionRule(){
	if(lookahead==OR){
		//printf(" %s", val);
		arraylist_add(stringArray,val);
		arraylist_add(intArray,lookahead);
		//strcpy(list[count],str); 
		match(OR);
		if(lookahead==EOLN){
			//printf(" ep");
			arraylist_add(stringArray,"Epsilon");
			arraylist_add(intArray,7);
			//strcpy(list[count],"epsilon");
		}
		rule();	productionRule();
	}
	else if(lookahead==SEMI){
		arraylist_add(finalString, stringArray);
		arraylist_add(finalInt,intArray);
		counter++;

		stringArray = arraylist_create(objEquals);
		intArray = arraylist_create(objEquals);
		return;}
	else if(lookahead==EOLN) {
		return;}
	else printf("\nPR");
}

void rule(){
	if(lookahead==NT){
		//printf(" %s", val);
		arraylist_add(stringArray,val);
		arraylist_add(intArray,lookahead);
		//strcpy(list[count],str); 
		match(NT);
		rule();
	}
	if(lookahead==T){
		//printf("\n%s", val);
		arraylist_add(stringArray,val);
		arraylist_add(intArray,lookahead);
                //strcpy(list[count],str);
        match(T);
        rule();
	}
	if(lookahead==EOLN){
		match(EOLN);
	}
//not sure here
	else return;

}

////////////////////////////
//////Gets all the terminal values and epsilon
/////////////////////////
void passOne(){
	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters
	int set=1;
	//printf("\nTHIS IS THE SIZE %d\n", s);
	r=arraylist_size(finalString);//r is row
	for (i=0;i<r;i++){
		c=arraylist_size(arraylist_get(finalString,i));
		Arraylist innerArray = arraylist_create(objEquals);
		Arraylist innerArrayInt = arraylist_create(objEquals);
		//Boolean finished=FALSE;
		for(j=0;j<c;j++){

			char *str=arraylist_get(arraylist_get(finalString,i),j);
			int *num=arraylist_get(arraylist_get(finalInt,i),j);
			//printf("%s",str);

			if (arraylist_get(arraylist_get(finalInt,i),(j+1))==GOES){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//arraylist_add(innerArray,":");
				//arraylist_add(innerArrayInt,8); //8 Is for :
				//printf("\n%s: ",str);
				set=1;
			}
			else if(num==OR){
				//finished=FALSE;
				//printf("");
				set=1;
			}
			else if(set && num==GOES){
				//printf("");
			}
			else if(set && num==NT){
				//////////////////
				//printf(""); 
				set=0;
			}
			else if(set && num==7){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//printf("Epsilon "); 
				set=0;
			}

			else if(set && num==T){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//printf("%s ",str);
				set=0;
			}
			else{
				//printf("Inside ELSE value is %s --", str);
			}
		}
		arraylist_add(p1Str,innerArray);
		arraylist_add(p1Int,innerArrayInt);

	}
}
////////////////////////////
//////Gets all the non-terminal values and immediate terminal
/////////////////////////
void passTwo(){
	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters
	int set=1;
	int prev=0;
	//printf("\nTHIS IS THE SIZE %d\n", s);
	r=arraylist_size(finalString);//r is row
	for (i=0;i<r;i++){
		c=arraylist_size(arraylist_get(finalString,i));
		Arraylist innerArray = arraylist_create(objEquals);
		Arraylist innerArrayInt = arraylist_create(objEquals);
		for(j=0;j<c;j++){
			char *str=arraylist_get(arraylist_get(finalString,i),j);
			int *num=arraylist_get(arraylist_get(finalInt,i),j);
			//printf("%s",str);

			if (arraylist_get(arraylist_get(finalInt,i),(j+1))==GOES){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//arraylist_add(innerArray,":");
				//arraylist_add(innerArrayInt,8); //8 Is for :
				//printf("\n%s: ",str);
				set=1;
			}
			else if(num==OR){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//printf("|");
				set=1; prev=0;
			}
			else if(set && num==GOES){
				//printf(""); 
				prev=0;
			}
			else if(set && num==NT){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//printf("%s ", str); 
				set=1; prev=NT;
			}
			else if(set && num==7){
				//printf(""); 
				set=0; prev=0;
			}

			else if(set && num==T&& prev==NT){
				arraylist_add(innerArray,str);
				arraylist_add(innerArrayInt,num);
				//printf("%s ",str);
				set=0; prev=0;
			}
			else if(prev==T){
				//printf("",str); 
				set=0;
			}
			else{
				//printf("Inside ELSE value is %s --", str);
				prev=0; set=0;
			}
		}
		arraylist_add(p2Str,innerArray);
		arraylist_add(p2Int,innerArrayInt);
	}
}

////////////
///Checks nonterminals, combines with terminals
////////////////
void passThree(){
	int size = arraylist_size(p2Str);
	int i;
	//First letter
	for (i=0; i<size; i++) {
		int size2 = arraylist_size(arraylist_get(p2Str, i));
 		char* first = arraylist_get(arraylist_get(p2Str, i), 0);
 		//printf("\n%d size2 ", size2);
 		Arraylist innerArray = arraylist_create(objEquals);
 		arraylist_add(innerArray, first);
 		//terminals
 		Arraylist terminals = getTerminal(first, arraylist_create(objEquals));
 		arraylist_remove(terminals, "\\:");
   		int size3 = arraylist_size(terminals);
   		int k;
   		//printf("\n%d size 3 - %s", size3, nonterminal);
   		for(k=0; k<size3; k++) {
    		char* value = arraylist_get(terminals, k);
    		 if (!contains(innerArray, value)) {
     	 		arraylist_add(innerArray, value);
    		}
   		}
 		arraylist_add(p3Str, innerArray);
	}
}


///////////////////////////
//Recurses through and updates terminals in p3
////////////////////
//updated holds nonterminals already processed
Arraylist getTerminal(char* key, Arraylist updated) {
	//printf("\n Key is : %s", key);
 	Arraylist terminalArray = arraylist_create(objEquals);
 	int size = arraylist_size(p2Str);
 	int i;
 	for (i=0; i<size; i++) {
   		char* first = arraylist_get(arraylist_get(p2Str, i), 0);
   		if (strcmp(first,key)==0) {
   			int size2 = arraylist_size(arraylist_get(p2Str, i));
   			int j;
   			Boolean finished=FALSE;
   			for (j=1; j<size2; j++) {
    			char* str = arraylist_get(arraylist_get(p2Str, i), j);
    			int num = arraylist_get(arraylist_get(p2Int, i), j);
    			if(num == OR){
     				finished=FALSE;
    			}
    			if(!finished){
    				//printf("\nStr is : %s", str);
     				if (num == NT && strcmp(key, str) != 0 && !contains(updated, str)) {
      					arraylist_add(updated, str);
      					Arraylist terminals = getTerminal(str, updated);
      					int size3 = arraylist_size(terminals);
      					int k;
      					for(k=0; k<size3; k++) {
       						char* value = arraylist_get(terminals, k);
       						if (!contains(terminalArray, value)) {
        						arraylist_add(terminalArray, value);
       						}
      					}
      					if(contains(terminalArray,"Epsilon")){
       						arraylist_remove(terminalArray,"Epsilon");
      					}
      					else{
    	   					finished=TRUE;
	      				}
    	 			}
    			}
   			}
  		}
	}
	//gets terminals
 	size = arraylist_size(p1Str);
 	i;
 	for (i=0; i<size; i++) {
   		char* first = arraylist_get(arraylist_get(p1Str, i), 0);
   		if (strcmp(first,key)==0) {
   			int size2 = arraylist_size(arraylist_get(p1Str, i));
   			int j;
   			for(j=1; j<size2; j++) {
    			arraylist_add(terminalArray, arraylist_get(arraylist_get(p1Str, i), j));
   			}
  		}
 	}
 	//arraylist_remove(terminalArray,":");
 	return terminalArray;
}
////////////////
//Prints out the firsts
/////////////
void printfinal(){
	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters

	//prints the CFG LL
	r=arraylist_size(p3Str);//r is row
	for (i=0;i<r;i++){
		printf("\n");
		c=arraylist_size(arraylist_get(p3Str,i));
		for(j=0;j<c;j++){
			char *str=arraylist_get(arraylist_get(p3Str,i),j);
			if(j==1){
				printf(": {");
			}
			printf("%s ", str);
		}
		printf("}");
	}
}

////////////
//Goes through and gets value in array
///////////
Boolean contains(Arraylist strList, char* input) {
	int size = arraylist_size(strList);
	int i;
	for (i=0; i<size; i++) {
		char* value = arraylist_get(strList, i);
  		if (strcmp(value, input)==0) {
   			return TRUE;
  		}
 	}
 	return FALSE;
}