#include "../includes/built_in.h"

AST* builtin_function_print(Visitor* visitor, AST** args, int size) {
    for(int i = 0; i < size; i++) {
        AST* arg = visitor_visist(visitor, args[i]);
        switch (arg->type) {
            case AST_STRING:
                printf("%s\n", arg->string_value);
                break;
            case AST_INT:
                printf("%d\n", arg->number);
                break;
            default:
                printf("%p\n", arg);
                break;

        }

        
        
    }

    return init_ast(AST_NOOP);
}