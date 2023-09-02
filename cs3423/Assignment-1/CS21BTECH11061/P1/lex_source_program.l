/***
YYLINENO option is enabled for printing line number when an error occurs 
***/
%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Pointer to Token and C filenames
char *TOK_FILE, *C_FILE;

// Bool Variables to handle goto and ifelse cases
bool ifelse = 0;
bool jump = 0;

// Pointer to Token and C file

FILE* TOKFILE;
FILE* CFILE;

// Function to write to C file
void writeC(char *text){
        fprintf(CFILE, "%s", text);
        return;
}

// Function to write to Token File
void writeTOKEN(char *type, char *text){
        fprintf(TOKFILE, "%s: %s\n", type, text);
        return;
}

// Function to quit program
void error(){
        char *toprint = "Error at pp";
        fprintf(TOKFILE, "%s%d\n", toprint, yylineno);
        printf("%s%d\n", toprint, yylineno);
        fprintf(CFILE, "\n%s%d\n", toprint, yylineno);
        exit(1);
}

%}

/* Some standard definations to help below*/

DIGIT [0-9]
NUM {DIGIT}+
UL [A-Z]
LL [a-z]
BACK ["\\"]
CH ({UL}|{LL}|{DIGIT})+
SPACE " "
WHITESPACE [" "|"\n"|"\t"]

/* Defining all operators, signs, punctuation, brackets*/

OPER ("+"|"-"|"*"|"/"|"_"|"="|"!"|"@"|"%")
OPERSPACE (" + "|" - "|" * "|" / "|" _ "|" = "|" ! "|" @ "|" % ")
SIGN ("eq"|"neq"|"gt"|"gteq"|"lt"|"lteq"|"and"|"or")
PUNC (":"|";"|",")
SP_SI ("("|"["|"]"|")")

/* Defining Strings and Characters */

STRING "\""([^\"]|[\\\"])*"\""
CHAR "\'"([^\']|[\\\'])"\'"

/* Defining reserved flow keywords*/

INCASE "in"{WHITESPACE}*"case"{WHITESPACE}*"that"
OTHERWISE "otherwise"
JUMP "jump"{WHITESPACE}*"to"
DO "do"
RETURN "return"
RESERVED ({INCASE}|{OTHERWISE}|{JUMP}|{DO})

/* Defining datatypes*/

DT_INT2 "integer_2"
DT_CHAR "character_1"
DT_STRING "string"
DT_VOID "null"
DT ({DT_INT2}|{DT_CHAR}|{DT_STRING}|{DT_VOID})

/* Defining labels and variables*/

LABEL "pp"{DIGIT}+
VARIABLE ({OPER})?{CH}

/* Defining helper square root regular expression*/

HELPER_ROOT {WHITESPACE}+"_"{WHITESPACE}+{NUM}

%%


{WHITESPACE} {
        writeC(yytext);
}


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
        writeC(yytext);
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
        writeC(yytext);
}


{PUNC} {
        writeTOKEN("punctuation", yytext);
        // Ignoring all ':' literals as it does not matter
        if(strcmp(yytext, ":")){
                writeC(yytext);
        }
        // If jump to does not have a label next to it. Now redunant
        if(!strcmp(yytext, ";")){
                jump = 0;
        }
}


{SP_SI} {
        writeTOKEN("special symbol", yytext);
        // Print brackets based on ifelse
        if(!strcmp(yytext, "[")){
                if(ifelse == 1)
                        writeC("(");
                else
                        writeC("{");
        }
        else if(!strcmp(yytext, "]")){
                if(ifelse == 1)
                        writeC(")");
                else
                        writeC("}");
        }
        else {
                writeC(yytext);
        }
}

{INCASE} {
        writeTOKEN("reserved keyword", "in case that");
        writeC("if");
        // For correct brackets
        ifelse = 1;
}

{DO} {
        writeTOKEN("reserved keyword", "do");
        // For correct brackets

        ifelse = 0;
}

{OTHERWISE} {
        writeTOKEN("reserved keyword", "otherwise");
        writeC("else");
}

{JUMP}/{WHITESPACE}{LABEL} {
        writeTOKEN("reserved keyword", "jump to");
        writeC("goto");
        // Handle if label is present
        jump = 1;
}

{JUMP} {
        // Handle if label is not present

        writeTOKEN("reserved keyword", "jump to");
        writeC("goto");
}

{RETURN} {
        writeTOKEN("reserved keyword", "return");
        writeC("return");
}

{DT} {
        // Print datatype accordingly
        writeTOKEN("datatype", yytext);
        if(!strcmp(yytext,"integer_2"))
                writeC("short");
        if(!strcmp(yytext,"character_1"))
                writeC("char");
        if(!strcmp(yytext,"null"))
                writeC("void");
        if(!strcmp(yytext,"string"))
                writeC("char *");
}

{LABEL} {
        // If a jump is to occur
        if(jump == 1){
                writeC(yytext);
                jump = 0;
        }
        writeTOKEN("label", yytext);
}

{SIGN} {
        writeTOKEN("reserved keyword", yytext);
        // Handle accordingly to sign
        if(!strcmp(yytext, "eq"))
                writeC("==");
        if(!strcmp(yytext, "neq"))
                writeC("!=");
        if(!strcmp(yytext, "lteq"))
                writeC("<=");
        if(!strcmp(yytext, "gteq"))
                writeC(">=");
        if(!strcmp(yytext, "gt"))
                writeC(">");
        if(!strcmp(yytext, "lt"))
                writeC("<");
        if(!strcmp(yytext, "and"))
                writeC("&&");
        if(!strcmp(yytext, "or"))
                writeC("||");
}

{VARIABLE}{HELPER_ROOT} {
        // Find variable in the string
        int l = 0;
        while(yytext[l] != ' ')
                l++;
        char *substr = malloc(l+1);
        strncpy(substr, yytext, l);
        substr[l] = '\0';
        // Print all token accordingly
        writeTOKEN("id", substr);
        writeTOKEN("operator", "_");
        writeTOKEN("constant", "2");
        writeC("sqrt(");
        writeC(substr);
        writeC(")");
        
        
}

{NUM}{HELPER_ROOT} {
        // Find number in the string
        int l = 0;
        while(yytext[l] != ' ')
                l++;
        char *substr = malloc(l+1);
        strncpy(substr, yytext, l);
        substr[l] = '\0';
        // Print all token accordingly
        writeTOKEN("constant", substr);
        writeTOKEN("operator", "_");
        writeTOKEN("constant", "2");
        writeC("sqrt(");
        writeC(substr);
        writeC(")");
        
}

{OPERSPACE} {
        writeTOKEN("operator", yytext);
        writeC(yytext);
}

{NUM} {
        writeTOKEN("constant", yytext);
        writeC(yytext);
} 

{VARIABLE} {
        writeTOKEN("id", yytext);
        writeC(yytext);
}

. {error();}

%%

int yywrap(){}
int main( int argc, char **argv)
{
        // Set the IO for the program
        ++argv; 
        --argc;

        // Default Names
        char *TOKN = "./TK/seq_tokens.txt";
        char *CN = "./TC/C.txt";

        if ( argc > 0 ){
                // Set file names using input file name
                char *temp = argv[0];
                yyin = fopen( temp, "r" );
                int n = strlen(temp);
                TOK_FILE = (char *)malloc(n+30);
                C_FILE = (char *)malloc(n+20);
                sprintf(TOK_FILE, "./TK/seq_tokens_%s",temp);
                sprintf(C_FILE, "./TC/C_%s",temp);
        }
        else{
                // If no input is provided
                yyin = stdin;
                TOK_FILE = TOKN;
                C_FILE = CN;
        }

        // Remove files if present beforehand
        remove(TOK_FILE);
        remove(C_FILE);

        // Open the req files
        TOKFILE = fopen(TOK_FILE, "w");
        CFILE = fopen(C_FILE, "w");

        // Print Name and Roll Number 
        fprintf(TOKFILE, "%s\n%s\n\n","Name: Vishal Vijay Devadiga", "ID: CS21BTECH11061");

        // Run the lexer
        yylex();

        // Close the output files
        fclose(TOKFILE);
        fclose(CFILE);

}