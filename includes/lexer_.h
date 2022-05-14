typedef struct lexer
{
    char c;
    unsigned int i;
    char* contents;
} LEXER;

LEXER* init_lexer(char* contents);
void move_lexer(LEXER* lexer);
char peek(LEXER* lexer, int a);
void skip_space(LEXER* lexer);