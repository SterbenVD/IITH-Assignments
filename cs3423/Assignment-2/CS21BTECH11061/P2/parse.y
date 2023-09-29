%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Defining yylex
int yylex();

// Defining error functions
int yyerror(char *s);
void parerror();

// Extern all required variables to use in lex
extern int yylineno;
extern FILE* PARFILE;
extern FILE* TOKFILE;
extern FILE* yyin;
extern char *yytext;
extern void writenl();

// Defining the enum for the parser
enum stat{funcdef, classdef, decstat, exprstat, callstat, callstatobj, loopstat, condstat, retstat};

// Defining the function to write to the parser file
void writedef(enum stat);

// Defining the struct for the log checking whether the current statement is in function/class and whether it has a return statement
struct log{
    bool isfunc;
    bool isclass;
    bool ret;
};

struct log logval = {false, false, false};

%}

%start	input
%token ID NUM STRINGVAL CHARVAL BOOLVAL
%token INT VOID BOOL STRING CHAR FLOAT
%token SCOPE CLASS
%token DECLARE EXPR CALL RETURN THIS
/* BRACK : {} ; BRACE: {} ; PAREN: ()*/
%token LBRACK RBRACK LBRACE RBRACE LPAREN RPAREN
%token SEMICOLON COMMA COLON
%token WHILE FOR DO INCASE OTHERWISE LOOP
%token UNAOP EQUAL ARROW
%token BINOP 
%token LOGICOP 
%token PREDOP NEG

/* Defining the precedence of the operators */
%left LOGICOP
%left PREDOP
%left NEG

%%

input: 
	| part input
	;

part: function
    | class LBRACE classbody RBRACE {logval.isclass = false; logval.ret = false;}
    ;

function: func LBRACE body RBRACE {logval.isfunc = false; if(logval.ret == false){parerror();} logval.ret = false;}
    ;

func: SCOPE type ID args {writedef(funcdef); logval.isfunc = true;}
    ;

class: CLASS ID argnumber {writedef(classdef); logval.isclass = true;}
    | CLASS ID {writedef(classdef); logval.isclass = true;}
    ;

args: argnumber LPAREN type ID helparg RPAREN
    | LPAREN RPAREN
    ;

helparg: 
    | COMMA type ID helparg
    ;


argnumber: LBRACK NUM RBRACK
    ;

type: INT | VOID | BOOL | STRING | CHAR | FLOAT ;

classbody:
    | dec classbody
    | function classbody
    ;

body: 
    | dec body
    | express body
    | loop body
    | ret body
    | unexp body
    | cal body
    ;

unexp: unaexpression SEMICOLON {writedef(exprstat);}
    ;

cal: CALL calobj SEMICOLON {writedef(callstatobj);}
    | CALL calmet SEMICOLON {writedef(callstat);}
    ;


methodarg: expression
    ;

calobj: ID ARROW ID argnumber LPAREN methodarg helpcal RPAREN 
    | ID ARROW ID LPAREN RPAREN
    | THIS ARROW ID argnumber LPAREN methodarg helpcal RPAREN {if(logval.isclass == false){parerror();}}
    | THIS ARROW ID LPAREN RPAREN {if(logval.isclass == false){parerror();}}
    ;

calmet: ID argnumber LPAREN methodarg helpcal RPAREN
    | ID LPAREN RPAREN
    ;

calhelper: CALL calobj
    | CALL calmet
    ;

helpcal: 
    | COMMA methodarg helpcal
    ;

dec: DECLARE type ID helpdec SEMICOLON {writedef(decstat);}
    | DECLARE ID ID helpdec SEMICOLON {writedef(decstat);}
    ;
  
helpdec: 
    | COMMA ID helpdec
    ;

express: exp SEMICOLON {writedef(exprstat);}

exp: EXPR ID EQUAL expression
    ;

expression: unaexpression
    | binexpression
    | expression LOGICOP expression
    | expression PREDOP expression
    | NEG expression
    | LPAREN expression RPAREN
    | ID
    | NUM
    | STRINGVAL
    | CHARVAL
    | BOOLVAL
    | calhelper
    ;

unaexpression: UNAOP LPAREN ID RPAREN
    | UNAOP LPAREN unaexpression RPAREN
    ;

binexpression: BINOP LPAREN expression COMMA expression RPAREN
    ;

ret: RETURN expression SEMICOLON {writedef(retstat); logval.ret = true;}
    | RETURN VOID SEMICOLON {writedef(retstat); logval.ret = true;}
    ;

loop: loopdec DO LBRACE body RBRACE
    | ifdec DO LBRACE body RBRACE other
    ;

loopdec: LOOP WHILE LPAREN expression RPAREN {writedef(loopstat);}
    | LOOP FOR LPAREN exp SEMICOLON expression SEMICOLON unaexpression RPAREN {writedef(loopstat);}
    | LOOP FOR LPAREN exp SEMICOLON expression SEMICOLON RPAREN {writedef(loopstat);}
    ;

ifdec: INCASE LPAREN expression RPAREN {writedef(condstat);}
    ;

other:
    | otherwise LBRACE body RBRACE
    ;

otherwise: OTHERWISE {writedef(condstat);}
    ;

%%

// Function to print error
int yyerror(char *s)
{
  extern int yylineno;	// defined and maintained in lex.c
  printf("ERROR: %s at symbol \"%s\" on line %d\n", s, yytext, yylineno);
  fprintf(PARFILE, "\nInvalid statement");
  fprintf(TOKFILE, "Invalid statement");
  exit(1);
}

// Function to print error
void parerror(){
        char *toprint = "Error at line number: ";
        fprintf(TOKFILE, "%s%d\n", toprint, yylineno);
        fprintf(PARFILE, "\nInvalid statement");
        printf("%s%d\n", toprint, yylineno);
        exit(1);
}

// Function to write newline to the parser file
void writenl(){
    fprintf(PARFILE, "\n");
}

// Function to write the definition of the statement
void writedef(enum stat x){
    fprintf(PARFILE, " : ");
    if(x == funcdef){
        fprintf(PARFILE, "function definition");
    }
    else if(x == classdef){
        fprintf(PARFILE, "class definition");
    }
    else if(x == decstat){
        fprintf(PARFILE, "declaration statement");
    }
    else if(x == exprstat){
        fprintf(PARFILE, "expression statement");
    }
    else if(x == callstat){
        fprintf(PARFILE, "call statement");
    }
    else if(x == callstatobj){
        fprintf(PARFILE, "call statement with object");
    }
    else if(x == loopstat){
        fprintf(PARFILE, "loop statement");
    }
    else if(x == condstat){
        fprintf(PARFILE, "conditional statement");
    }
    else if(x == retstat){
        fprintf(PARFILE, "return statement");
    }
}

// Main function
int main(int argc, char **argv){

    ++argv;
    --argc;


    // Defining strings for the file names
    char *TOKN = "./TP2/seq_tokens_";
    char *PARN = "./TP2/parser_";
    
    char * TOK_NAME, *PAR_NAME;

    int n = strlen(argv[0]) - 5;

    // Take the number as a substring
    char* substr = (char *)malloc(n);
    strncpy(substr, argv[0], n-1);
    substr[n-1] = '\0';

    TOK_NAME = (char *)malloc(n+30);
    PAR_NAME = (char *)malloc(n+30);

    // Set the file names
    strncpy(TOK_NAME, TOKN, 17);
    strncpy(PAR_NAME, PARN, 13);
    strncpy(TOK_NAME+17, substr, n-1);
    strncpy(PAR_NAME+13, substr, n-1);
    strncpy(TOK_NAME+17+n-1, ".txt", 4);
    strncpy(PAR_NAME+13+n-1, ".parsed", 7);

    // Remove files if present beforehand
    remove(TOK_NAME);
    remove(PAR_NAME);

    // Open the req files
    yyin = fopen( argv[0], "r" );
    TOKFILE = fopen(TOK_NAME, "w");
    PARFILE = fopen(PAR_NAME, "w");

    // Print Name and Roll Number 
    fprintf(TOKFILE, "%s\n%s\n\n","Name: Vishal Vijay Devadiga", "ID: CS21BTECH11061");

    // Call the parser
    yyparse();

    // Close the output files
    fclose(TOKFILE);
    fclose(PARFILE);
}