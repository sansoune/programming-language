#ifndef yassine_token_h
#define yassine_token_h


#include "lexer_.h"

enum TokenType {
    NUMBER,
    STRING,
    EQUAL,
    ID,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,
    PLUS,
    MINUS,
    COMMA,
    STAR,
    LT,
    GT,
    SLASH,
};


struct _Token {
    int type;
    char* data;
    int line;
};

typedef struct _Token Token;
Token* create_token(int type, char* data, int line);
void destroy_token(Token* token);



Token* add_token(LEXER* lexer, Token* token);



#endif