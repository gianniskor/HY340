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
    
    strcpy(yylval->cont->class_type, tt.class_type);
    strcpy(yylval->cont->val, tt.val);
    strcpy(yylval->cont->type, tt.type);
    
    printf("line %d, val %s\n", line, yylval->cont->val);
}