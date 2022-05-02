#include "../includes/AST.h"

AST* init_ast(int type)
{
    AST* ast = calloc(1, sizeof(AST));
    ast->type = type;
    
    ast->variable_definition_name = (void*)0;
    ast->variable_definition_value = (void*)0;

    ast->variable_reference_name = (void*)0;

    ast->function_call_name = (void*)0;
    ast->function_call_arguments = (void*)0;
    ast->function_call_arguments_size = 0;

    ast->string_value = (void*)0;

    return ast;
}