#include "lexLib.hpp"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern int count;
extern comment_list_t* comment_head;
extern comment_list_t* comment_tail;

void comment_push(int yylineno){
    comment_list_t* p = malloc(sizeof(comment_list_t));
    if(p==NULL){
        printf("error during malloc in comment_push\n");
        exit(-1);
    }
    p->line=yylineno;
    p->next = NULL;
    if(comment_head == NULL){
        comment_head = p;
        comment_tail = p;
    }else{
        comment_tail->next = p;
        comment_tail = p;
    }
}

void comment_delete() {
    if (comment_head == NULL) return;
    if (comment_head == comment_tail) {
        free(comment_head);
        comment_head = comment_tail = NULL;
        return;
    }
    comment_list_t* p = comment_head;
    while (p->next != comment_tail) {
        p = p->next;
    }
    free(comment_tail);
    comment_tail = p;
    comment_tail->next = NULL;
}

char *comment_line(int start, int end) {
    char *str = malloc(20);
    if (str == NULL) {
        printf("failed malloc in comment_line function\n");
        exit(-1);
    }
    sprintf(str, "%d - %d", start, end);
    return str;
}