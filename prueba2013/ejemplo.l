/*** Secci�n de declaraciones ***/

%{
#include <stdio.h>
%}

%option noyywrap

%%
    /*** Secci�n de reglas ***/

[0-9]+  {
            printf("Se encontro el numero   \" %s \" \n", yytext);
        }
[abc]   {
            printf("Se encontro el caracter \" %s \" \n", yytext);
        }


.       {   /* Ignora todos los dem�s caracteres. */   }

%%
/*** Secci�n de c�digo en C ***/

int main(void)
{
    /* Ejecuta el ''lexer'', y despu�s termina. */
    printf("*************** EJEMPLO DE ANALIZADOR LEXICO ***************\n");
    printf("Ingrese un conjunto de caracteres:\n");
    printf(">>> ");
    yylex();
    return 0;
}