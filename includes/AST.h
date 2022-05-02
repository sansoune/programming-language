#ifndef AST_H
#define AST_H

#include <stdlib.h>


typedef struct AST_STRUCT
{
    enum {
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE_REFERENCE,
        AST_FUNCTION_CALL,
        AST_STRING
    } type;   

    char* variable_definition_name;
    struct AST_STRUCT* variable_definition_value;


    char* variable_reference_name;

    char* function_call_name;
    struct AST_STRUCT** function_call_arguments;
    size_t function_call_arguments_size;

    char* string_value;

} AST;

AST* init_ast(int type);

#endif