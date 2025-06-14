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
                    token_cont_t tt = {yytext,const_cast<char*>("IF"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval,yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return IF;
                }

"else"          {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("ELSE"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return ELSE;
                }
"while"         {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("WHILE"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return WHILE;
                }
"for"           {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("for"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return FOR;
                }
"function"      {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("FUNCTION"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return FUNCTION;
                }
"return"        {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("RETURN"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RETURN;
                }
"break"         {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("BREAK"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return BREAK;
                }
"continue"      {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("CONTINUE"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return CONTINUE;
                }
"and"           {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("AND"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return AND;
                }
"not"           {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("NOT"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NOT;
                }
"or"            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("OR"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return OR;
                }
"local"         {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LOCAL"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LOCAL;
                }
"true"          {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("TRUE"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    //apo yylval.stringConst = strdup(yytext); se -> yylval.intValue = 0;
                    yylval.boolConst = 1;
                    return TRUE;
                }
"false"         {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("FALSE"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    //yylval.stringConst = strdup(yytext);
                    yylval.boolConst = 0;
                    return FALSE;
                }
"nil"           {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("NIL"),const_cast<char*>("KEYWORD")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NIL;
                }
"="             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("ASSIGN"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return EQUALS;
                }
"+"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("PLUS"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PLUS;
                }
"-"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("MINUS"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MINUS;
                }
"*"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("MULTIPLY"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MULTIPLY;
                }
"/"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("DIVISION"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DIVIDE;
                }
"%"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("MODULO"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MOD;
                }
"=="            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("EQUAL"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_EQUALS;
                }
"!="            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("NONEQUAL"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt); 
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return NOT_EQUALS;
                }
"++"            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("PLUS_PLUS"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PLUS_PLUS;
                }
"--"            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("MINUS_MINUS"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return MINUS_MINUS;
                }
">"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("GREATER_THAN"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt); 
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return GREATER;
                }
"<"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LESS_THAN"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LESS;
                }
">="            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("GREATER_EQUAL_THAN"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return GREATER_EQUALS;
                }
"<="            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LESS_EQUAL_THAN"),const_cast<char*>("OPERATOR")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LESS_EQUALS;
                }
"{"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LEFT_BRACE"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_CBRACKET;
                }
"}"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("RIGHT_BRACE"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_CBRACKET;
                }
"["             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LEFT_BRACKET"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_BRACKET;
                }
"]"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("RIGHT_BRACKET"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_BRACKET;
                }
"("             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("LEFT_PARENTHESIS"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return LEFT_PARENTHESIS;
                }
")"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("RIGHT_PARENTHESIS"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return RIGHT_PARENTHESIS;
                }
";"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("SEMICOLON"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return SEMICOLON;
                }
","             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("COMMA"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return COMMA;
                }
":"             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("COLON"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return COLON;
                }
"::"            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("DOUBLE_COLON"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_COLON;
                }
"."             {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("PERIOD"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return PERIOD;
                }
".."            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("DOUBLE_PERIOD"),const_cast<char*>("PUNCTUATION")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return DOUBLE_PERIOD;
                }

{ID}            {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("ID"),const_cast<char*>("IDENTIFIER")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.stringConst = strdup(yytext);
                    return ID;
                }
{INT}           {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("INT"),const_cast<char*>("INTCONST")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
                    yylval.intConst = atoi(yytext);
                    return INT;
                }
{REAL}          {
                    counter++;
                    token_cont_t tt = {yytext,const_cast<char*>("REAL"),const_cast<char*>("REALCONST")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
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
                    token_cont_t tt = {yytext,yytext,const_cast<char*>("STRING")};
                    //add_token(yylval, yylineno, counter, tt);
                    //print_alpha_token(yylineno, counter, tt);
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
                    token_cont_t tt = {yytext,const_cast<char*>("COMMENT"),const_cast<char*>("LINE_COMMENT")};
                    //add_token(yylval,yylineno-1,counter,tt);
                    //print_alpha_token(yylineno-1, counter, tt);
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
                        token_cont_t tt = {str, const_cast<char*>("COMMENT"), const_cast<char*>("BLOCK_COMMENT")};
                        //add_token(yylval, comment_tail->line, counter, tt);
                        //print_alpha_token(comment_tail->line, counter, tt);
                        free(str);
                        comment_delete();
                        BEGIN(INITIAL);
                    } else {
                        counter++;
                        char *str = comment_line(comment_tail->line, yylineno);
                        token_cont_t tt = {str, const_cast<char*>("COMMENT"), const_cast<char*>("NESTED_COMMENT")};
                        //add_token(yylval, comment_tail->line, counter, tt);
                        //print_alpha_token(comment_tail->line, counter, tt);
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
    if (strcmp(tt.class_type, const_cast<char*>("LINE_COMMENT")) == 0 || strcmp(tt.class_type, const_cast<char*>("COMMENT")) == 0 ||
        strcmp(tt.class_type, const_cast<char*>("BLOCK_COMMENT")) == 0 || strcmp(tt.class_type, const_cast<char*>("NESTED_COMMENT")) == 0) {
        printf("\n");
    }else if (strcmp(tt.class_type, const_cast<char*>("ID")) == 0 || strcmp(tt.class_type, const_cast<char*>("STRING")) == 0) {
        printf("<- char*\n");
    }else if (strcmp(tt.class_type, const_cast<char*>("INT")) == 0) {
        printf("<- int\n");
    }else if (strcmp(tt.class_type, const_cast<char*>("REAL")) == 0) {
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