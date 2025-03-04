typedef struct token_cont_t{
    char *val;
    char *type;
    char *class_type;
}token_cont_t;

typedef struct alpha_token_t{
    int line;
    int count;
    struct token_cont_t *cont;
    struct alpha_token_t *next;
}alpha_token_t;

typedef struct token_list{
    alpha_token_t *t;
    struct token_list *next;
}token_list_t;

typedef struct comment_list{
    int line;
    int closing;
    struct comment_list* next;
}comment_list_t;