%{
#include <stdio.h>

%}

%option noyywrap

palabra	"public" 

%%

-?[0-9]+ {
            printf("ENTERO\n");
            return 0;
        }

{palabra} {
            printf("-1\n");
            return 0;
        }

%%

int main(){
	printf("EJEMPLO LEX \n");
	while(true){
	yylex();
	
}
    return 0;
}

