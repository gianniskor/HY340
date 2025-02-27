typedef struct token_cont_t{
    char *val;
    char *type;
    char *class_type;
}token_cont_t;

typedef struct alpha_token_t{
    int line;
    int count;
    token_cont_t *cont;
    token_t *next;
}token_t;
