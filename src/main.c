#include <stdio.h>
#include <stdlib.h>
#include "../includes/util.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"


int main(int argc,char** argv)
{
    if(argc < 2) {
        printf("please specify a file \n");
        exit(1);
    }

    char* source = read_file(argv[1]);
    LEXER* lexer = init_lexer(source);
    Parser* parser = init_parser(lexer);
    AST* root = parser_parse(parser);

    printf("%d\n", root->type);
    printf("%ld\n", root->compound_size);
    
    

    // free(tokens);
    free(source);

    return 0;
}