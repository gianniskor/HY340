%{
    #include "lexLib.hpp"
    #include "syntax.hpp"
    #define YY_DECL int yylex(void)
    int counter = 0;
    void add_token(alpha_token_t *yylval, int line, int counter, token_cont_t tt);
    void print_alpha_token(int yylineno, int counter, token_cont_t tt);
    void comment_push(int yylineno);
    void comment_delete();
    char* replace_chars(char* str);
    char *comment_line(int start, int end);
    void print_tokens();
    void free_token_list();
    token_list_t* head = NULL;
    token_list_t* tail = NULL;
    comment_list_t* comment_head = NULL;
    comment_list_t* comment_tail = NULL;
    /*allaksa to name tou count se counter giati eixe error epeidh einai global*/
%}

%option noyywrap
%option yylineno
%option header-file = "al.hpp"

ID      [a-zA-Z][a-zA-Z0-9_]*
INT     [0-9]+
REAL    [0-9]+\.+[0-9]+
STRING  \"([^"\\]|\\.|\\\n)*\"
WSPACE  [ \n\t\v]
LINE_REGEX "//"
COMMENT_REGEX "/*"

%x      COMMENT
%x      LINE_COMMENT

%%

"if"            {
                    counter++;
                    token_cont_t tt = {yytext,"IF","KEYWORD"};
                    //add_token(yylval,yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return IF;
                }

"else"          {
                    counter++;
                    token_cont_t tt = {yytext,"ELSE","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return ELSE;
                }
"while"         {
                    counter++;
                    token_cont_t tt = {yytext,"WHILE","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return WHILE;
                }
"for"           {
                    counter++;
                    token_cont_t tt = {yytext,"for","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return FOR;
                }
"function"      {
                    counter++;
                    token_cont_t tt = {yytext,"FUNCTION","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return FUNCTION;
                }
"return"        {
                    counter++;
                    token_cont_t tt = {yytext,"RETURN","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RETURN;
                }
"break"         {
                    counter++;
                    token_cont_t tt = {yytext,"BREAK","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return BREAK;
                }
"continue"      {
                    counter++;
                    token_cont_t tt = {yytext,"CONTINUE","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return CONTINUE;
                }
"and"           {
                    counter++;
                    token_cont_t tt = {yytext,"AND","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return AND;
                }
"not"           {
                    counter++;
                    token_cont_t tt = {yytext,"NOT","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NOT;
                }
"or"            {
                    counter++;
                    token_cont_t tt = {yytext,"OR","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return OR;
                }
"local"         {
                    counter++;
                    token_cont_t tt = {yytext,"LOCAL","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LOCAL;
                }
"true"          {
                    counter++;
                    token_cont_t tt = {yytext,"TRUE","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    //apo yylval.stringConst = strdup(yytext); se -> yylval.intValue = 0;
                    yylval.boolConst = 1;
                    return TRUE;
                }
"false"         {
                    counter++;
                    token_cont_t tt = {yytext,"FALSE","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    //yylval.stringConst = strdup(yytext);
                    yylval.boolConst = 0;
                    return FALSE;
                }
"nil"           {
                    counter++;
                    token_cont_t tt = {yytext,"NIL","KEYWORD"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NIL;
                }
"="             {
                    counter++;
                    token_cont_t tt = {yytext,"ASSIGN","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return EQUALS;
                }
"+"             {
                    counter++;
                    token_cont_t tt = {yytext,"PLUS","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PLUS;
                }
"-"             {
                    counter++;
                    token_cont_t tt = {yytext,"MINUS","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MINUS;
                }
"*"             {
                    counter++;
                    token_cont_t tt = {yytext,"MULTIPLY","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MULTIPLY;
                }
"/"             {
                    counter++;
                    token_cont_t tt = {yytext,"DIVISION","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DIVIDE;
                }
"%"             {
                    counter++;
                    token_cont_t tt = {yytext,"MODULO","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MOD;
                }
"=="            {
                    counter++;
                    token_cont_t tt = {yytext,"EQUAL","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_EQUALS;
                }
"!="            {
                    counter++;
                    token_cont_t tt = {yytext,"NONEQUAL","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt); 
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NOT_EQUALS;
                }
"++"            {
                    counter++;
                    token_cont_t tt = {yytext,"PLUS_PLUS","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PLUS_PLUS;
                }
"--"            {
                    counter++;
                    token_cont_t tt = {yytext,"MINUS_MINUS","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MINUS_MINUS;
                }
">"             {
                    counter++;
                    token_cont_t tt = {yytext,"GREATER_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt); 
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return GREATER;
                }
"<"             {
                    counter++;
                    token_cont_t tt = {yytext,"LESS_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LESS;
                }
">="            {
                    counter++;
                    token_cont_t tt = {yytext,"GREATER_EQUAL_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return GREATER_EQUALS;
                }
"<="            {
                    counter++;
                    token_cont_t tt = {yytext,"LESS_EQUAL_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LESS_EQUALS;
                }
"{"             {
                    counter++;
                    token_cont_t tt = {yytext,"LEFT_BRACE","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_CBRACKET;
                }
"}"             {
                    counter++;
                    token_cont_t tt = {yytext,"RIGHT_BRACE","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_CBRACKET;
                }
"["             {
                    counter++;
                    token_cont_t tt = {yytext,"LEFT_BRACKET","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_BRACKET;
                }
"]"             {
                    counter++;
                    token_cont_t tt = {yytext,"RIGHT_BRACKET","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_BRACKET;
                }
"("             {
                    counter++;
                    token_cont_t tt = {yytext,"LEFT_PARENTHESIS","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_PARENTHESIS;
                }
")"             {
                    counter++;
                    token_cont_t tt = {yytext,"RIGHT_PARENTHESIS","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_PARENTHESIS;
                }
";"             {
                    counter++;
                    token_cont_t tt = {yytext,"SEMICOLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return SEMICOLON;
                }
","             {
                    counter++;
                    token_cont_t tt = {yytext,"COMMA","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return COMMA;
                }
":"             {
                    counter++;
                    token_cont_t tt = {yytext,"COLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return COLON;
                }
"::"            {
                    counter++;
                    token_cont_t tt = {yytext,"DOUBLE_COLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_COLON;
                }
"."             {
                    counter++;
                    token_cont_t tt = {yytext,"PERIOD","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PERIOD;
                }
".."            {
                    counter++;
                    token_cont_t tt = {yytext,"DOUBLE_PERIOD","PUNCTUATION"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_PERIOD;
                }

{ID}            {
                    counter++;
                    token_cont_t tt = {yytext,"ID","IDENTIFIER"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return ID;
                }
{INT}           {
                    counter++;
                    token_cont_t tt = {yytext,"INT","INTCONST"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.intConst = atoi(yytext);
                    return INT;
                }
{REAL}          {
                    counter++;
                    token_cont_t tt = {yytext,"REAL","REALCONST"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.realConst = atof(yytext);
                    return REAL;
                }
{STRING}        {
                    counter++;
                    // remove quotes
                    char* str = strdup(yytext + 1);
                    str[strlen(str) - 1] = '\0';
                    str = replace_chars(str);
                    yytext = str;
                    token_cont_t tt = {yytext,yytext,"STRING"};
                    //add_token(yylval, yylineno, counter, tt);
                    print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return STRING;  
                }
\"[^\"]*        {
                    printf("Error, Unclosed String.\n");
                    return -1;
                }
{WSPACE}        {
                }
{LINE_REGEX}    {
                    BEGIN(LINE_COMMENT);
                }
<LINE_COMMENT>\n {
                    counter++;
                    token_cont_t tt = {yytext,"COMMENT","LINE_COMMENT"};
                    //add_token(yylval,yylineno-1,counter,tt);
                    print_alpha_token(yylineno-1, counter, tt);
                    BEGIN(INITIAL);
                }
<LINE_COMMENT>. {
                }
{COMMENT_REGEX} {
                    //comment_push(yylineno);
                    BEGIN(COMMENT);
                }
<COMMENT>"/*"   {
                    comment_push(yylineno);
                }
<COMMENT>"*/"   {
                    if (comment_head != NULL && comment_head->next == NULL) {
                        counter++;
                        char *str = comment_line(comment_tail->line, yylineno);
                        token_cont_t tt = {str, "COMMENT", "BLOCK_COMMENT"};
                        //add_token(yylval, comment_tail->line, counter, tt);
                        print_alpha_token(comment_tail->line, counter, tt);
                        free(str);
                        comment_delete();
                        BEGIN(INITIAL);
                    } else {
                        counter++;
                        char *str = comment_line(comment_tail->line, yylineno);
                        token_cont_t tt = {str, "COMMENT", "NESTED_COMMENT"};
                        //add_token(yylval, comment_tail->line, counter, tt);
                        print_alpha_token(comment_tail->line, counter, tt);
                        free(str);
                        comment_delete();
                    }
                }
<COMMENT><<EOF>>    {
                        printf("error, block comment not closed.\n");
                        return 2;
                    }
<COMMENT>.|\n       {
                    }
<<EOF>>             {
                        return 2;
                    }
                    
%%
void print_alpha_token(int yylineno, int counter, token_cont_t tt) {
    printf("%d:\t#%d\t\"%s\"\t%s\t%s\t",
            yylineno,
            counter,
            tt.val,
            tt.class_type,
            tt.type);
    if (strcmp(tt.class_type, "LINE_COMMENT") == 0 || strcmp(tt.class_type, "COMMENT") == 0 ||
        strcmp(tt.class_type, "BLOCK_COMMENT") == 0 || strcmp(tt.class_type, "NESTED_COMMENT") == 0) {
        printf("\n");
    }else if (strcmp(tt.class_type, "ID") == 0 || strcmp(tt.class_type, "STRING") == 0) {
        printf("<- char*\n");
    }else if (strcmp(tt.class_type, "INT") == 0) {
        printf("<- int\n");
    }else if (strcmp(tt.class_type, "REAL") == 0) {
        printf("<- float\n");
    }else {
        printf("<- enumerated\n");
    }
}
/* int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Error opening file\n");
        return 1;
    }
    alpha_token_t* token = NULL;
    if(!(yyin = fopen(argv[1], "r"))) {
        printf("Error reading file\n");
        return 1;
    }
    while(1) {
        token = (alpha_token_t*)malloc(sizeof(alpha_token_t));
        token->cont = NULL;
        if(alpha_yylex(token) == 2) break;
    }
    print_tokens();
    free_token_list();
    fclose(yyin);
    return 0;
} */