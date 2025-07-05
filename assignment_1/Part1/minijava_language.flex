%{
#include <iostream>
%}

%option noyywrap

%%

    /* KEYWORDS */
"public"                  { std::cout << "PUBLIC"; }
"class"                   { std::cout << "CLASS"; }
"static"                  { std::cout << "STATIC"; }
"void"                    { std::cout << "VOID"; }
"main"                    { std::cout << "MAIN"; }
"String"                  { std::cout << "STRING"; }
"int"                     { std::cout << "INT"; }
"boolean"                 { std::cout << "BOOLEAN"; }
"if"                      { std::cout << "IF"; }
"else"                    { std::cout << "ELSE"; }
"while"                   { std::cout << "WHILE"; }
"return"                  { std::cout << "RETURN"; }
"System.out.println"      { std::cout << "PRINTLN"; }
"true"                    { std::cout << "TRUE"; }
"false"                   { std::cout << "FALSE"; }
"this"                    { std::cout << "THIS"; }
"new"                     { std::cout << "NEW"; }

    /* SYMBOLS */
"{"                       { std::cout << "LBRACE"; }
"}"                       { std::cout << "RBRACE"; }
"("                       { std::cout << "LPAREN"; }
")"                       { std::cout << "RPAREN"; }
"["                       { std::cout << "LBRACKET"; }
"]"                       { std::cout << "RBRACKET"; }
";"                       { std::cout << "SEMICOLON"; }
","                       { std::cout << "COMMA"; }
"."                       { std::cout << "DOT"; }
"="                       { std::cout << "ASSIGN"; }
"&&"                      { std::cout << "AND"; }
"||"                      { std::cout << "OR"; }
"<"                       { std::cout << "LT"; }
">"                       { std::cout << "GT"; }
"=="                      { std::cout << "EQ"; }
"+"                       { std::cout << "PLUS"; }
"-"                       { std::cout << "MINUS"; }
"*"                       { std::cout << "MULT"; }
"!"                       { std::cout << "NOT"; }
"\""                      { std::cout << "QUOTE"; }
"%"                       { std::cout << "PERCENT"; }
"$"                       { std::cout << "DOLLAR"; }
"@"                       { std::cout << "AT"; }

    /* LITERALS */
[0-9]+                    { std::cout << "INTEGER_LITERAL"; } // Integer literals
[a-zA-Z_][a-zA-Z0-9_]*    { std::cout << "IDENTIFIER"; }      // Identifiers

    /* COMMENTS */
"//".*                    { /* Ignore single-line comments */ }
"/*"(.|\n)*?"*/"          { /* Ignore multi-line comments */ }

    /* WHITESPACE */
[ \t\n\r]+                { /* Ignore whitespace */ }

    /* ERROR HANDLING */
.                         { printf("Unrecognized character: %s\n", yytext); exit(1); }

%%
