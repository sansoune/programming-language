#include <stdio.h>
#include <stdlib.h>
#include "../includes/util.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/visitor.h"

#define MAX_LIMIT 256

int main(int argc,char** argv)
{
    if(argc >= 2) {
        char* extension = strrchr(argv[1], '.');
        
        if (strcmp(extension, ".yassine") == 0) {
            char* source = read_file(argv[1]);
            LEXER* lexer = init_lexer(source);
            Parser* parser = init_parser(lexer);
            AST* root = parser_parse(parser, parser->scope);
            Visitor* visitor = init_visitor();
            visitor_visist(visitor, root);
            free(source);
        }
        else {
            printf("file type not supported\n");
            exit(1);
        }        
    }
    
    else {
        char input[MAX_LIMIT];
        printf("\033[0;32m");
        printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
        printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
        printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  \n");
        printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  \n");
        printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
        printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
        printf("\033[0m");
        while(1) {
            printf("yassine> ");
            fgets(input,MAX_LIMIT, stdin);
            if(strcmp(input, "exit\n") == 0) {
                break;
            }
            else if(strcmp(input, "help\n") == 0) {
                printf("\033[0;36m");
                printf("usage: yassine [file]\n");
                printf("\033[0m");
                printf("\tfile: file to execute\n");
                printf("\tfile must be a .yassine file\n");
                printf("\33[0;36m");
                printf("commands:\n");
                printf("\33[0m");
                printf("\texit: exit the program\n");
                printf("\thelp: display this message\n");
            }
            else {
                LEXER* lexer = init_lexer(input);
                Parser* parser = init_parser(lexer);
                AST* root = parser_parse(parser, parser->scope);
                Visitor* visitor = init_visitor();
                visitor_visist(visitor, root);
            }
        }
    }

    
    

    
    

    return 0;
}