#include <stdio.h>
#include <stdlib.h>
#include "../includes/util.h"
#include "../includes/lexer.h"


int main(int argc,char** argv)
{
    if(argc < 2) {
        printf("please specify a file \n");
        exit(1);
    }

    char* source = read_file(argv[1]);
    LEXER* lexer = init_lexer(source);
    Token* token = (void*)0;

    while((token = lexing(lexer)) != (void*)0 ) {
        printf("TOKEN(%d %s %d)\n", token->type,token->data,token->line);
    }
    
    

    // free(tokens);
    free(source);

    return 0;
}