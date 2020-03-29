%option noyywrap
%option yylineno

%{
#include <stdio.h>
//#include <iostream>
#include <stdlib.h>
#include <string>
#include "parser.tab.h"

using namespace std;
extern void yyerror(const char*);

int linum = 1;
int yylex();

struct token* newToken(string name, long long number_value, int linum);
%}


%x comment
WHITESPACE [ \t]

%%
"[" {BEGIN(comment);} 
<comment>{<<EOF>> {yyerror("Comment not closed"); yyterminate();}
    "]" {BEGIN(INITIAL);}
    .   ;
    "\n"  {linum++;}
}

0|-?[1-9]+[0-9]*    {yylval.token = newToken("NUM" , strtoll(yytext ,NULL, 10), linum); return NUM;} // dodatnie ujemne liczby

"PLUS"      {yylval.token = newToken("PLUS", 0, linum); return PLUS;}  
"MINUS"     {yylval.token = newToken("MINUS", 0, linum); return MINUS;}     
"TIMES"     {yylval.token = newToken("TIMES", 0, linum); return TIMES;}
"DIV"       {yylval.token = newToken("DIV", 0, linum); return DIV;}
"MOD"       {yylval.token = newToken("MOD", 0, linum); return MOD;}

"EQ"        {yylval.token = newToken("EQ", 0, linum); return EQ;}
"NEQ"       {yylval.token = newToken("NEQ", 0, linum); return NEQ;}
"LE"        {yylval.token = newToken("LE", 0, linum); return LE;}
"GE"        {yylval.token = newToken("GE", 0, linum); return GE;}
"LEQ"       {yylval.token = newToken("LEQ", 0, linum); return LEQ;}
"GEQ"       {yylval.token = newToken("GEQ", 0, linum); return GEQ;}

"DECLARE"   {yylval.token = newToken("DECLARE", 0, linum); return DECLARE;}
"BEGIN"     {yylval.token = newToken("BEGIN", 0, linum); return BEGIN2;}
"ASSIGN"    {yylval.token = newToken("ASSIGN", 0, linum); return ASSIGN;}
"THEN"      {yylval.token = newToken("THEN", 0, linum); return THEN;}
"ELSE"      {yylval.token = newToken("ELSE", 0, linum); return ELSE;}
"ENDIF"     {yylval.token = newToken("ENDIF", 0, linum); return ENDIF;}
"ENDWHILE"  {yylval.token = newToken("ENDWHILE", 0, linum); return ENDWHILE;}
"WHILE"     {yylval.token = newToken("WHILE", 0, linum); return WHILE;}
"ENDDO"     {yylval.token = newToken("ENDDO", 0, linum); return ENDDO;}
"FOR"       {yylval.token = newToken("FOR", 0, linum); return FOR;}
"DO"        {yylval.token = newToken("DO", 0, linum); return DO;}
"IF"        {yylval.token = newToken("IF", 0, linum); return IF;}
"END"       {yylval.token = newToken("END", 0, linum); return END;}
"FROM"      {yylval.token = newToken("FROM", 0, linum); return FROM;}
"TO"        {yylval.token = newToken("TO", 0, linum); return TO;}
"ENDFOR"    {yylval.token = newToken("ENDFOR", 0, linum); return ENDFOR;}
"READ"      {yylval.token = newToken("READ", 0, linum); return READ;}
"WRITE"     {yylval.token = newToken("WRITE", 0, linum); return WRITE;}
"DOWNTO"    {yylval.token = newToken("DOWNTO", 0, linum); return DOWNTO;}

";"         {yylval.token = newToken(";", 0, linum); return ';';}
"("         {yylval.token = newToken("(", 0, linum); return '(';}
":"         {yylval.token = newToken(":", 0, linum); return ':';}
")"         {yylval.token = newToken(")", 0, linum); return ')';}
","         {yylval.token = newToken(",", 0, linum); return ',';}

[_a-z]+     {yylval.token = newToken(strdup(yytext), 0, linum); return PID;}

[_a-z0-9]+ {const char* place = yytext; string place_str = place; string error = "Error in declaration name " + place_str + " in line " + to_string(linum); yyerror(&error[0]); yyterminate();}

{WHITESPACE}    {;}
\n              {linum++;}
.               {string error = "Error in line " + to_string(linum); yyerror(&error[0]); yyterminate();}


%%


//([0-9]+[_a-zA-Z]*|[_a-zA-Z]*[0-9]+)+ {const char* place = yytext; string place_str = place; string error = "Error in declaration name " + place_str + " in line " + to_string(linum); yyerror(&error[0]); yyterminate();}