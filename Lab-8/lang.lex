%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int line = 0;
%}

%option noyywrap

IDENTIFIER            [a-zA-Z][a-zA-Z0-9]*
NUMBER                0|0.[0-9]*|[1-9][0-9]+|[1-9][0-9]*.[0-9]+
BASE_TYPE             bool|double|int|char|string
RESERVED_WORD         if|else|while|for|Console.Read|Console.Write|Console.WriteLine|.ToInt32
OPERATOR              "+"|"-"|"*"|"/"|"%"
SEPARATOR             "["|"]"|"{"|"}"|"("|")"|":"|","|";"
RELATIONAL_OPERATOR   "="|"=="|"!="|"<"|">"|"<="|">="|"&&"
STRING                \"[a-zA-Z0-9]+\"
CHAR                  \'[a-zA-Z0-9]\'
NEW_LINE              [\n]+
EMPTY                 [ \t]+

WRONG_IDENTIFIER      [0-9]+[a-zA-Z0-9]*
WRONG_NUMBER          [0-9]+.
WRONG_OPERATOR        "=!"|"=<"|"=>"|"&"
WRONG_STRING          [a-zA-Z0-9]+\"|\"[a-zA-Z0-9]+
WRONG_CHAR            \'[a-zA-Z0-9]+\'
%%

{BASE_TYPE}|{RESERVED_WORD}       {printf("Reserved word: %s\n", yytext);}
{OPERATOR}                        {printf("Operator: %s\n", yytext);}
{RELATIONAL_OPERATOR}             {printf("Relational operator: %s\n", yytext);}
{SEPARATOR}                       {printf("Separator: %s\n", yytext);}
{NUMBER}                          {printf("Number: %s\n", yytext);}
{STRING}                          {printf("String: %s\n", yytext);}
{CHAR}                            {printf("Character: %s\n", yytext);}
{IDENTIFIER}		              {printf("Identifier: %s\n", yytext);}

{EMPTY} 	                      {}
{NEW_LINE}                        {line++;}

{WRONG_IDENTIFIER}		          {printf("Illegal identifier at line: %d ('%s')\n", line, yytext); return -1;}
{WRONG_NUMBER}		              {printf("Illegal number at line: %d ('%s')\n", line, yytext); return -1;}
{WRONG_OPERATOR}                  {printf("Illegal operator at line %d ('%s')\n", line, yytext); return -1;}
{WRONG_STRING}                    {printf("Illegal string at line %d ('%s')\n", line, yytext); return -1;}
{WRONG_CHAR}                      {printf("Illegal char at line %d ('%s')\n", line, yytext); return -1;}

%%

void main(argc, argv)
int argc;
char** argv;
{
if (argc > 1)
{
    FILE *file;
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        exit(1);
    }
    yyin = file;
}

yylex();
}