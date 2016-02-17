%{
#include "tokens.h"
int lineno=1;
int counter=0;
char* val;
int semiCount=0;
%}
%%
[A-Z] 		  	{val=strdup(yytext);counter++;return NT;}
[a-z]   		{val=strdup(yytext);counter++;return T ;}
\-\-\>   		{val=strdup(yytext);counter++;return GOES;}
\;	     		{val=strdup(yytext);semiCount++;counter++;return SEMI;}
\|	    		{val=strdup(yytext);counter++;return OR;}
[\n\r]+[ \t]*[\n\r]*    {val=strdup(yytext);counter++;return EOLN;}
[ \t]+			;
.			;
%%
