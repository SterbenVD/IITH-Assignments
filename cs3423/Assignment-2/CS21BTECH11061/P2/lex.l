%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

// Pointer to Token and C file
FILE* TOKFILE;
FILE* PARFILE;

void writeTOKEN(char *, char *);
void writePARSE();
void writenl();
void error();
void inputtaker(int, char **);

%}

/* Some standard definations to help below*/

DIGIT [0-9]
NUM {DIGIT}+
FLOAT {NUM}"."{NUM}
UL [A-Z]
LL [a-z]
BACK ["\\"]
CH ({UL}|{LL}|{DIGIT})+
UNDERSCORE "_"
SPACE " "
WHITESPACE ({SPACE}|"\t"|"\n")

/* Defining strings and chars*/
STRING "\""([^\"]|"\"")*"\""
CHAR "\'"([^\']|"\'")"\'"

/* Defining identifer*/
VARIABLE ({UL}|{LL})({UL}|{LL}|{DIGIT}|{UNDERSCORE})*

/* Defining all operators*/
EQUAL "="
BIN_OPER ("mul"|"add"|"sub"|"div")
UNA_OPER ("postincr"|"postdecr")
PRED ("eq"|"ne"|"gt"|"geq"|"lt"|"leq"|"neg")
LOGIC ("and"|"or")
BOOLVAL ("true"|"false")
BRACKETS ("("|")"|"{"|"}"|"["|"]")
PUNC (";"|":"|",")
ARROW "->"

/* Defining all keywords*/
INCASE "in"{SPACE}*"case"{SPACE}*"that"
CONTROL_KEYWORD ("while"|"do"|"for"|"otherwise")
START_KEYWORD ("declare"|"expr"|"call"|"loop")
RETURN "return"
THIS "this"

/* Defining data types*/
CLASS "class"
SCOPE ("global"|"local")
TYPE ("int"|"float"|"char"|"bool"|"void"|"string")

%%

{WHITESPACE} { writePARSE(yytext); }


{STRING} {
        int n = strlen(yytext);
        // Print opening quotes
        writeTOKEN("punctuation", "\"");

        // Take the actual string as a substring
        char* substr = (char *)malloc(n-1);
        strncpy(substr, yytext+1, n-2);
        substr[n-2] = '\0';
        writeTOKEN("constant", substr);
        free(substr);

        // Print closing quotes
        writeTOKEN("punctuation", "\"");
        return STRINGVAL;
}

{CHAR} {
        int n = strlen(yytext);
        // Print opening quotes
        writeTOKEN("punctuation", "'");

        // Take the actual string as a substring
        char* substr = (char *)malloc(n-1);
        strncpy(substr, yytext+1, n-2);
        substr[n-2] = '\0';
        writeTOKEN("constant", substr);
        free(substr);

        // Print closing quotes
        writeTOKEN("punctuation", "'");
        return CHARVAL;
}

{BRACKETS} {
        writeTOKEN("special symbol", yytext);
        if(!strcmp(yytext, "[")){
                return LBRACK;
        }
        else if(!strcmp(yytext, "]")){
                return RBRACK;
        }
        else if(!strcmp(yytext, "(")){
                return LPAREN;
        }
        else if(!strcmp(yytext, ")")){
                return RPAREN;
        }
        else if(!strcmp(yytext, "{")){
                return LBRACE;
        }
        else if(!strcmp(yytext, "}")){
                return RBRACE;
        }
}

{ARROW} {
        writeTOKEN("operator", "->");
        return ARROW;
}

{PUNC} {
        writeTOKEN("punctuation", yytext);
        if(!strcmp(yytext, ";")){
                return SEMICOLON;
        }
        else if(!strcmp(yytext, ":")){
                return COLON;
        }
        else if(!strcmp(yytext, ",")){
                return COMMA;
        }
}

{BIN_OPER} {
        writeTOKEN("operator", yytext); 
        return BINOP;
}

{UNA_OPER} {
        writeTOKEN("operator", yytext); 
        return UNAOP;
}

{LOGIC} {
        writeTOKEN("reserved keyword", yytext); 
        return LOGICOP;
}

{BOOLVAL} {
        writeTOKEN("reserved keyword", yytext);
        return BOOLVAL;
}

{PRED} {
        writeTOKEN("reserved keyword", yytext); 
        if(!strcmp(yytext, "neg")){
                return NEG;
        }
        else{
                return PREDOP;
        }
}

{EQUAL} {
        writeTOKEN("operator", yytext); 
        return EQUAL;
}

{INCASE} {
        writeTOKEN("reserved keyword", "in case that"); 
        return INCASE;
}

{CONTROL_KEYWORD} {
        writeTOKEN("reserved keyword", yytext); 
        if(!strcmp(yytext, "for")){
                return FOR;
        }
        else if(!strcmp(yytext, "while")){
                return WHILE;
        }
        else if(!strcmp(yytext, "do")){
                return DO;
        }
        else if(!strcmp(yytext, "otherwise")){
                return OTHERWISE;
        }
}

{START_KEYWORD} {
        writeTOKEN("reserved keyword", yytext);
        if(!strcmp(yytext, "loop")){
                return LOOP;
        }
        else if(!strcmp(yytext, "declare")){
                return DECLARE;
        }
        else if(!strcmp(yytext, "expr")){
                return EXPR;
        }
        else if(!strcmp(yytext, "call")){
                return CALL;
        }

}

{RETURN} {
        writeTOKEN("reserved keyword", yytext);
        return RETURN;
}

{SCOPE} {
        writeTOKEN("reserved keyword", yytext);
        return SCOPE;
}

{CLASS} {
        writeTOKEN("reserved keyword", "class");
        return CLASS;
}

{TYPE} {
        writeTOKEN("datatype", yytext);
        if(!strcmp(yytext, "int")){
                return INT;
        }
        else if(!strcmp(yytext, "float")){
                return FLOAT;
        }
        else if(!strcmp(yytext, "char")){
                return CHAR;
        }
        else if(!strcmp(yytext, "bool")){
                return BOOL;
        }
        else if(!strcmp(yytext, "void")){
                return VOID;
        }
        else if(!strcmp(yytext, "string")){
                return STRING;
        }
}

{THIS} {
        writeTOKEN("reserved keyword", yytext);
        return THIS;
        }

{VARIABLE} {
        writeTOKEN("id", yytext);
        return ID;
}

{NUM} {
        writeTOKEN("constant", yytext);
        return NUM;
}

. {error();}

%%

// Function to write to Token File
void writeTOKEN(char *type, char *text){
        fprintf(TOKFILE, "%s : %s\n", type, text);
        writePARSE(text);
        return;
}

// Function to quit program
void error(){
        char *toprint = "Error at line number: ";
        fprintf(TOKFILE, "%s%d\n", toprint, yylineno);
        fprintf(PARFILE, "\nInvalid Token");
        printf("%s%d\n", toprint, yylineno);
        exit(1);
}

// Function to write to Parse File
void writePARSE(char *text){
        fprintf(PARFILE, "%s", text);
        return;
}

int yywrap() {
        return 1;
}
