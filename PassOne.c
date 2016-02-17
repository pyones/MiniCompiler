#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"
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


	prodList();
	if(lookahead!=0){
		printf("error");
		return 0;
	}	

	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters

	//printf("\nTHIS IS THE SIZE %d\n", s);
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


}

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
		for(j=0;j<c;j++){
			char *str=arraylist_get(arraylist_get(finalString,i),j);
			int *num=arraylist_get(arraylist_get(finalInt,i),j);
			//printf("%s",str);

			if (arraylist_get(arraylist_get(finalInt,i),(j+1))==GOES){
				arraylist_add(p1Str,val);
				arraylist_add(p1Int,lookahead);
				arraylist_add(p1Str,":");
				arraylist_add(p1Int,8); //8 Is for :
				printf("\n%s: ",str);
				set=1;
			}
			else if(num==OR){
				printf("");set=1;
			}
			else if(set && num==GOES){
				printf("");
			}
			else if(set && num==NT){
				printf(""); set=0;
			}
			else if(set && num==7){
				arraylist_add(p1Str,val);
				arraylist_add(p1Int,lookahead);
				printf("Epsilon "); set=0;
			}

			else if(set && num==T){
				arraylist_add(p1Str,val);
				arraylist_add(p1Int,lookahead);
				printf("%s ",str);
				set=0;
			}
			else{
				//printf("Inside ELSE value is %s --", str);
			}

		}
	}
}

void passTwo(){
	int r,c;//=arraylist_size(arraylist_get(finalString,0));
	int i,j; //counters
	int set=1;
	int prev=0;
	//printf("\nTHIS IS THE SIZE %d\n", s);
	r=arraylist_size(finalString);//r is row
	for (i=0;i<r;i++){
		c=arraylist_size(arraylist_get(finalString,i));
		for(j=0;j<c;j++){
			char *str=arraylist_get(arraylist_get(finalString,i),j);
			int *num=arraylist_get(arraylist_get(finalInt,i),j);
			//printf("%s",str);

			if (arraylist_get(arraylist_get(finalInt,i),(j+1))==GOES){
				arraylist_add(p1Str,val);
				arraylist_add(p1Int,lookahead);
				arraylist_add(p1Str,":");
				arraylist_add(p1Int,8); //8 Is for :
				printf("\n%s: ",str);
				set=1;
			}
			else if(num==OR){
				printf("");set=1; prev=0;
			}
			else if(set && num==GOES){
				printf(""); prev=0;
			}
			else if(set && num==NT){
				arraylist_add(p2Str,val);
				arraylist_add(p2Int,lookahead);
				printf("%s", str); set=1; prev=NT;
			}
			else if(set && num==7){
				printf(""); set=0; prev=0;
			}

			else if(set && num==T&& prev==NT){
				printf("",str);
				set=0; prev=0;
			}
			else{
				//printf("Inside ELSE value is %s --", str);
			}
		}
	}
}