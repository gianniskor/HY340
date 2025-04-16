%{
    #include "lexLib.hpp"
    #include "syntax.hpp"
    #define YY_DECL int yylex(void)
    int count = 0;
    void add_token(alpha_token_t *yylval, int line, int count, token_cont_t tt);
    void print_alpha_token(int yylineno, int count, token_cont_t tt);
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
                    count++;
                    token_cont_t tt = {yytext,"IF","KEYWORD"};
                    //add_token(yylval,yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return IF;
                }

"else"          {
                    count++;
                    token_cont_t tt = {yytext,"ELSE","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return ELSE;
                }
"while"         {
                    count++;
                    token_cont_t tt = {yytext,"WHILE","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return WHILE;
                }
"for"           {
                    count++;
                    token_cont_t tt = {yytext,"for","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return FOR;
                }
"function"      {
                    count++;
                    token_cont_t tt = {yytext,"FUNCTION","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return FUNCTION;
                }
"return"        {
                    count++;
                    token_cont_t tt = {yytext,"RETURN","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return RETURN;
                }
"break"         {
                    count++;
                    token_cont_t tt = {yytext,"BREAK","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return BREAK;
                }
"continue"      {
                    count++;
                    token_cont_t tt = {yytext,"CONTINUE","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return CONTINUE;
                }
"and"           {
                    count++;
                    token_cont_t tt = {yytext,"AND","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return AND;
                }
"not"           {
                    count++;
                    token_cont_t tt = {yytext,"NOT","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return NOT;
                }
"or"            {
                    count++;
                    token_cont_t tt = {yytext,"OR","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return OR;
                }
"local"         {
                    count++;
                    token_cont_t tt = {yytext,"LOCAL","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LOCAL;
                }
"true"          {
                    count++;
                    token_cont_t tt = {yytext,"TRUE","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return TRUE;
                }
"false"         {
                    count++;
                    token_cont_t tt = {yytext,"FALSE","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return FALSE;
                }
"nil"           {
                    count++;
                    token_cont_t tt = {yytext,"NIL","KEYWORD"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return NIL;
                }
"="             {
                    count++;
                    token_cont_t tt = {yytext,"ASSIGN","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return EQUALS;
                }
"+"             {
                    count++;
                    token_cont_t tt = {yytext,"PLUS","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return PLUS;
                }
"-"             {
                    count++;
                    token_cont_t tt = {yytext,"MINUS","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return MINUS;
                }
"*"             {
                    count++;
                    token_cont_t tt = {yytext,"MULTIPLY","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return MULTIPLY;
                }
"/"             {
                    count++;
                    token_cont_t tt = {yytext,"DIVISION","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return DIVIDE;
                }
"%"             {
                    count++;
                    token_cont_t tt = {yytext,"MODULO","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return MOD;
                }
"=="            {
                    count++;
                    token_cont_t tt = {yytext,"EQUAL","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return DOUBLE_EQUALS;
                }
"!="            {
                    count++;
                    token_cont_t tt = {yytext,"NONEQUAL","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt); 
                    print_alpha_token(yylineno, count, tt);
                
                    return NOT_EQUALS;
                }
"++"            {
                    count++;
                    token_cont_t tt = {yytext,"PLUS_PLUS","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return PLUS_PLUS;
                }
"--"            {
                    count++;
                    token_cont_t tt = {yytext,"MINUS_MINUS","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return MINUS_MINUS;
                }
">"             {
                    count++;
                    token_cont_t tt = {yytext,"GREATER_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt); 
                    print_alpha_token(yylineno, count, tt);
                
                    return GREATER;
                }
"<"             {
                    count++;
                    token_cont_t tt = {yytext,"LESS_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LESS;
                }
">="            {
                    count++;
                    token_cont_t tt = {yytext,"GREATER_EQUAL_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return GREATER_EQUALS;
                }
"<="            {
                    count++;
                    token_cont_t tt = {yytext,"LESS_EQUAL_THAN","OPERATOR"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LESS_EQUALS;
                }
"{"             {
                    count++;
                    token_cont_t tt = {yytext,"LEFT_BRACE","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LEFT_BRACKET;
                }
"}"             {
                    count++;
                    token_cont_t tt = {yytext,"RIGHT_BRACE","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return RIGHT_BRACKET;
                }
"["             {
                    count++;
                    token_cont_t tt = {yytext,"LEFT_BRACKET","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LEFT_CBRACKET;
                }
"]"             {
                    count++;
                    token_cont_t tt = {yytext,"RIGHT_BRACKET","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return RIGHT_CBRACKET;
                }
"("             {
                    count++;
                    token_cont_t tt = {yytext,"LEFT_PARENTHESIS","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return LEFT_PARENTHESIS;
                }
")"             {
                    count++;
                    token_cont_t tt = {yytext,"RIGHT_PARENTHESIS","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return RIGHT_PARENTHESIS;
                }
";"             {
                    count++;
                    token_cont_t tt = {yytext,"SEMICOLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return SEMICOLON;
                }
","             {
                    count++;
                    token_cont_t tt = {yytext,"COMMA","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return COMMA;
                }
":"             {
                    count++;
                    token_cont_t tt = {yytext,"COLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return COLON;
                }
"::"            {
                    count++;
                    token_cont_t tt = {yytext,"DOUBLE_COLON","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return DOUBLE_COLON;
                }
"."             {
                    count++;
                    token_cont_t tt = {yytext,"PERIOD","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return PERIOD;
                }
".."            {
                    count++;
                    token_cont_t tt = {yytext,"DOUBLE_PERIOD","PUNCTUATION"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return DOUBLE_PERIOD;
                }

{ID}            {
                    count++;
                    token_cont_t tt = {yytext,"ID","IDENTIFIER"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
                    return ID;
                }
{INT}           {
                    count++;
                    token_cont_t tt = {yytext,"INT","INTCONST"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                                   return INT;
                }
{REAL}          {
                    count++;
                    token_cont_t tt = {yytext,"REAL","REALCONST"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                                   return REAL;
                }
{STRING}        {
                    count++;
                    // remove quotes
                    char* str = strdup(yytext + 1);
                    str[strlen(str) - 1] = '\0';
                    str = replace_chars(str);
                    yytext = str;
                    token_cont_t tt = {yytext,yytext,"STRING"};
                    //add_token(yylval, yylineno, count, tt);
                    print_alpha_token(yylineno, count, tt);
                
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
                    count++;
                    token_cont_t tt = {yytext,"COMMENT","LINE_COMMENT"};
                    //add_token(yylval,yylineno-1,count,tt);
                    print_alpha_token(yylineno-1, count, tt);
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
                        count++;
                        char *str = comment_line(comment_tail->line, yylineno);
                        token_cont_t tt = {str, "COMMENT", "BLOCK_COMMENT"};
                        //add_token(yylval, comment_tail->line, count, tt);
                        print_alpha_token(comment_tail->line, count, tt);
                        free(str);
                        comment_delete();
                        BEGIN(INITIAL);
                    } else {
                        count++;
                        char *str = comment_line(comment_tail->line, yylineno);
                        token_cont_t tt = {str, "COMMENT", "NESTED_COMMENT"};
                        //add_token(yylval, comment_tail->line, count, tt);
                        print_alpha_token(comment_tail->line, count, tt);
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
void print_alpha_token(int yylineno, int count, token_cont_t tt) {
    printf("%d:\t#%d\t\"%s\"\t%s\t%s\t",
            yylineno,
            count,
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