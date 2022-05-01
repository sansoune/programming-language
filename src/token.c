#include "../includes/token.h"
#include <stdlib.h>

Token* create_token(int type, char* data, int line) {
    Token* tok = calloc(1, sizeof(Token));
    tok->type = type;
    tok->data = data;
    tok->line = line;
    return tok;
}

void destroy_token(Token* token) {
    free(token);
}

Token* add_token(LEXER* lexer, Token* token) {
    move_lexer(lexer);

    return token;
}


