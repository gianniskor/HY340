%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int yylex();
    extern int yyerror(char*);
    extern FILE* yyin;
    extern int yylineno;

    /* Add your custom data structures and functions here */
    typedef struct {
        char* text;
        char* type;
        char* category;
    } token_cont_t;

    typedef struct token_list {
        token_cont_t token;
        struct token_list* next;
    } token_list_t;

    token_list_t* head = NULL;
    token_list_t* tail = NULL;

    void add_token(token_cont_t token) {
        token_list_t* new_node = (token_list_t*)malloc(sizeof(token_list_t));
        new_node->token = token;
        new_node->next = NULL;

        if (head == NULL) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
%}

%union {
    int num;
    char* id;
    token_cont_t token;
}

%token <token> ID INTEGER REAL STRING
%token <token> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE
%token <token> AND NOT OR LOCAL TRUE FALSE NIL
%token <token> PLUS MINUS MULTIPLY DIVISION MODULO
%token <token> EQUAL NONEQUAL PLUS_PLUS MINUS_MINUS
%token <token> GREATER_THAN LESS_THAN GREATER_EQUAL_THAN LESS_EQUAL_THAN
%token <token> LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token <token> LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMICOLON COMMA
%token <token> COLON DOUBLE_COLON PERIOD DOUBLE_PERIOD
%token <token> COMMENT LINE_COMMENT BLOCK_COMMENT NESTED_COMMENT

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

program:    assignments expressions
            |   /* empty */
            ;

expression: INTEGER
            | REAL
            | STRING
            | ID
            | expression '+' expression
            | expression '-' expression
            | expression '*' expression
            | expression '/' expression
            | '(' expression ')'
            | '-' expression %prec UMINUS
            ;

expr:       expression '\n'    { printf("Valid expression\n"); }
            ;

expressions: expressions expr
            | expr
            ;

assignment: ID '=' expression '\n' { printf("Assignment to %s\n", $1.text); }
            ;

assignments: assignments assignment
            |   /* empty */
            ;

%%

int yyerror(char* msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
    return 0;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    yyparse();

    /* Print all tokens */
    token_list_t* current = head;
    while (current != NULL) {
        printf("Token: %s, Type: %s, Category: %s\n",
               current->token.text,
               current->token.type,
               current->token.category);
        token_list_t* to_free = current;
        current = current->next;
        free(to_free->token.text);
        free(to_free);
    }

    return 0;
}