#include "lexLib.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

extern int count;
extern comment_list_t* comment_head;
extern comment_list_t* comment_tail;

void comment_push(int yylineno) {
    comment_list_t* p = new comment_list_t();
    if(p == nullptr) {
        std::cout << "error during memory allocation in comment_push" << std::endl;
        exit(-1);
    }
    p->line = yylineno;
    p->next = nullptr;
    if(comment_head == nullptr) {
        comment_head = p;
        comment_tail = p;
    } else {
        comment_tail->next = p;
        comment_tail = p;
    }
}

void comment_delete() {
    if (comment_head == nullptr) return;
    if (comment_head == comment_tail) {
        delete comment_head;
        comment_head = comment_tail = nullptr;
        return;
    }
    comment_list_t* p = comment_head;
    while (p->next != comment_tail) {
        p = p->next;
    }
    delete comment_tail;
    comment_tail = p;
    comment_tail->next = nullptr;
}

char* comment_line(int start, int end) {
    char* str = new char[20];
    if (str == nullptr) {
        std::cout << "failed memory allocation in comment_line function" << std::endl;
        exit(-1);
    }
    sprintf(str, "%d - %d", start, end);
    return str;
}