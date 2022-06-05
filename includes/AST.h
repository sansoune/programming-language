#ifndef AST_H
#define AST_H

#include <stdlib.h>


typedef struct AST_STRUCT
{
    enum {
        AST_VARIABLE_DEFINITION,
        AST_FUNCTION_DEFINITION,
        AST_VARIABLE,
        AST_INT,
        AST_BINOP,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
        AST_NOOP,
    } type;   

    struct SCOPE_STRUCT* scope;

    char* variable_definition_name;
    struct AST_STRUCT* variable_definition_value;

    struct AST_STRUCT* function_definition_body;
    char* function_definition_name;
    struct AST_STRUCT** function_definition_arguments;
    size_t function_definition_arguments_size;
    

    char* variable_name;

    char* function_call_name;
    struct AST_STRUCT** function_call_arguments;
    size_t function_call_arguments_size;

    char* string_value;

    int number;
    struct AST_STRUCT* left;
    struct AST_STRUCT* right;
    int op;
    

    struct AST_STRUCT** compound_value;
    size_t compound_size;

} AST;

AST* init_ast(int type);

#endif