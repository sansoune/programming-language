typedef struct lexer
{
    char c;
    unsigned int i;
    char* contents;
} LEXER;

LEXER* init_lexer(char* contents);
void move_lexer(LEXER* lexer);
void skip_space(LEXER* lexer);