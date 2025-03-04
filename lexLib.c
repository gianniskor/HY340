//#include "al.h"
#include "lexLib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern int count;

void add_token(alpha_token_t *yylval, int line, int count, token_cont_t tt){
    
    int sizeClass = strlen(tt.class_type)+1;
    int sizeType = strlen(tt.type)+1;
    int sizeVal = strlen(tt.val)+1;

    if (yylval->cont == NULL) {
        yylval->cont = (token_cont_t*)malloc(sizeof(token_cont_t));
    }
    
    yylval->line = line;
    yylval->count = count;
    yylval->cont->class_type = (char*)malloc(sizeClass * sizeof(char));
    yylval->cont->type = (char*)malloc(sizeType * sizeof(char));
    yylval->cont->val = (char*)malloc(sizeVal * sizeof(char));

    if((strcmp(tt.class_type,"LINE_COMMENT"))==0){
        free(yylval->cont->val);
        int sizeN = sizeof("\"comment_value\"");
        yylval->cont->val = (char*)malloc(sizeN*sizeof(char));
        strcpy(yylval->cont->val, "\"comment_value\"");
        strcpy(yylval->cont->class_type, tt.class_type);
        strcpy(yylval->cont->type, tt.type);
    }else{
        strcpy(yylval->cont->class_type, tt.class_type);
        strcpy(yylval->cont->val, tt.val);
        strcpy(yylval->cont->type, tt.type);
    }

    printf("line %d, val %s, type %s, classtype %s\n", line, yylval->cont->val,yylval->cont->type,yylval->cont->class_type);
}
char* replace_chars(char* str){
    char* new_str = (char*)malloc(strlen(str) + 1);
    int i = 0;
    int j = 0;
    while(str[i]){
        if(str[i] == '\\'){
            i++;
            switch(str[i]){
                case 'n':
                    new_str[j] = '\n';
                    break;
                case 't':
                    new_str[j] = '\t';
                    break;
                case '\\':
                    new_str[j] = '\\';
                    break;
                case '\'':
                    new_str[j] = '\'';
                    break;
                case '\"':
                    new_str[j] = '\"';
                    break;
                default:
                    new_str[j] = str[i];
                    break;
            }
        }else{
            new_str[j] = str[i];
        }
        i++;
        j++;
    }
    new_str[j] = '\0';
    strcpy(str,new_str);
    free(new_str);
    return str;
}