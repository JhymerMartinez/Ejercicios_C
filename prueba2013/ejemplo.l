/*** Sección de declaraciones ***/

%{
#include <stdio.h>
%}

%option noyywrap

%%
    /*** Sección de reglas ***/

[0-9]+  {
            printf("Se encontro el numero   \" %s \" \n", yytext);
        }
[abc]   {
            printf("Se encontro el caracter \" %s \" \n", yytext);
        }


.       {   /* Ignora todos los demás caracteres. */   }

%%
/*** Sección de código en C ***/

int main(void)
{
    /* Ejecuta el ''lexer'', y después termina. */
    printf("*************** EJEMPLO DE ANALIZADOR LEXICO ***************\n");
    printf("Ingrese un conjunto de caracteres:\n");
    printf(">>> ");
    yylex();
    return 0;
}