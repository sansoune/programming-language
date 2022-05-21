#include "../includes/lexer.h"


LEXER* init_lexer(char* contents) {
    LEXER* lexer = calloc(1, sizeof(LEXER));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    // printf("%c\n", lexer->c);
}

void move_lexer(LEXER* lexer) {
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i++;
        lexer->c = lexer->contents[lexer->i];
    }
}

char peek(LEXER* lexer, int a) {
    return lexer->contents[MIN(lexer->i + a, strlen(lexer->contents))];
}

void skip_space(LEXER* lexer) {
    while(lexer->c == ' ' || lexer->c == 10) {
        move_lexer(lexer);
    }
}

void skip_comment(LEXER* lexer) {
    while(lexer->c != '\n') {
        if(lexer->c == '\0') {
            break;
        }
        move_lexer(lexer);
    }
    // skip_space(lexer);
}


Token* lexing(LEXER* lexer) {
    int line = 1;

    while (lexer->c != '\0' &&  lexer->i < strlen(lexer->contents)) {
        if(lexer->c == ' ' || lexer->c == 10) {
            skip_space(lexer);
        }
        if(lexer->c == '/' && peek(lexer, 1) == '/') {
            skip_comment(lexer);
        }
        if(isdigit(lexer->c)) {
            return collect_number(lexer);
        }
        if(isalnum(lexer->c)) {
            return collect_id(lexer);
            
        }
        if(lexer->c == '"') {
            return parse_string(lexer);
        }
        switch (lexer->c) {
            case '=' :
                return add_token(lexer, create_token(EQUAL, current_char(lexer), line));
                break;
            case '(':
                return add_token(lexer, create_token(LPAREN, current_char(lexer), line));
                break;
            case ')':
                return add_token(lexer, create_token(RPAREN, current_char(lexer), line));
                break;
            case '{':
                return add_token(lexer, create_token(LBRACE, current_char(lexer), line));
                break;
            case '}':
                return add_token(lexer, create_token(RBRACE, current_char(lexer), line));
                break;
            case ';':
                return add_token(lexer, create_token(SEMICOLON, current_char(lexer), line));
                break;
            case ',':
                return add_token(lexer, create_token(COMMA, current_char(lexer), line));
                break;
            case '+':
                return add_token(lexer, create_token(PLUS, current_char(lexer), line));
                break;

        }   

    }
    if(lexer->c == '\n') {
     line++;
    }

    return create_token(TOKEN_EOF, "\0", line);

}

//function to parse numbers
Token* collect_number(LEXER* lexer) {
    char* number = calloc(1, sizeof(char));
    int i = 0;
    while(isdigit(lexer->c)) {
        number[i] = lexer->c;
        i++;
        move_lexer(lexer);
    }
    return create_token(NUMBER, number, 0);
}


// a function that parses a string
Token* parse_string(LEXER* lexer) {
    move_lexer(lexer);

    char* id = calloc(1, sizeof(char));
    id[0] = '\0';
    while(lexer->c != '"') {
        char* s = current_char(lexer);
        id = realloc(id, (strlen(id) + strlen(s) + 1) * sizeof(char));
        strcat(id, s);
        move_lexer(lexer);
    }

    move_lexer(lexer);
    
    return create_token(STRING, id, 0);
}



Token* collect_id(LEXER* lexer) {
    char* id = calloc(1, sizeof(char));
    id[0] = '\0';
    while(isalpha(lexer->c)) {
        char* s = current_char(lexer);
        id = realloc(id, (strlen(id) + strlen(s) + 1) * sizeof(char));
        strcat(id, s);
        move_lexer(lexer);
    }
    

    return create_token(ID, id, 0);
}

char* current_char(LEXER* lexer) {
    char* c = calloc(2, sizeof(char));
    c[0] = lexer->c;
    c[1] = '\0';
    return c;   
}

