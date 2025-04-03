//#include "al.h"
#include "lexLib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern token_list_t* head;
extern token_list_t* tail;
extern int count;

void add_token(alpha_token_t *yylval, int line, int count, token_cont_t tt) {
    token_list_t* new_node = (token_list_t*)malloc(sizeof(token_list_t));
    new_node->t = (alpha_token_t*)malloc(sizeof(alpha_token_t));

    new_node->t->line = line;
    new_node->t->count = count;
    new_node->t->cont = (token_cont_t*)malloc(sizeof(token_cont_t));

    int sizeClass = strlen(tt.class_type) + 1;
    int sizeType = strlen(tt.type) + 1;
    int sizeVal = strlen(tt.val) + 1;
    
    new_node->t->cont->class_type = (char*)malloc(sizeClass * sizeof(char));
    new_node->t->cont->type = (char*)malloc(sizeType * sizeof(char));
    new_node->t->cont->val = (char*)malloc(sizeVal * sizeof(char));

    if (strcmp(tt.class_type, "LINE_COMMENT") == 0) {
        strcpy(new_node->t->cont->val, "");
    } else {
        strcpy(new_node->t->cont->val, tt.val);
    }
    
    strcpy(new_node->t->cont->class_type, tt.class_type);
    strcpy(new_node->t->cont->type, tt.type);
    new_node->next = NULL;
    
    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

void print_tokens() {
    printf("----------------|\tLEXICAL ANALYSIS \t|----------------\n\n");
    token_list_t* current = head;    
    while (current != NULL) {
        printf("%d:\t#%d\t\"%s\"\t%s\t%s\t",
               current->t->line,
               current->t->count,
               current->t->cont->val,
               current->t->cont->class_type,
               current->t->cont->type);
        if (strcmp(current->t->cont->class_type, "LINE_COMMENT") == 0 || strcmp(current->t->cont->class_type, "COMMENT") == 0 ||
            strcmp(current->t->cont->class_type, "BLOCK_COMMENT") == 0 || strcmp(current->t->cont->class_type, "NESTED_COMMENT") == 0) {
            printf("\n");
        }else if (strcmp(current->t->cont->type, "ID") == 0 || strcmp(current->t->cont->class_type, "STRING") == 0) {
            printf("<- char*\n");
        }else if (strcmp(current->t->cont->type, "INT") == 0) {
            printf("<- int\n");
        }else if (strcmp(current->t->cont->type, "REAL") == 0) {
            printf("<- float\n");
        }else {
            printf("<- enumerated\n");
        }
        current = current->next;
    }
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

void free_token_list(){
    token_list_t* current = head;
    
    while (current != NULL) {
        token_list_t* temp = current;

        free(current->t->cont->class_type);
        free(current->t->cont->type);
        free(current->t->cont->val);
        free(current->t->cont);
        free(current->t);
        
        current = current->next;
        free(temp);
    }
    head = NULL;
    tail = NULL;
}