#ifndef SCOPE_H
#define SCOPE_H

#include "AST.h"

typedef struct SCOPE_STRUCT
{
    AST** function_definitions;
    size_t function_definitions_size;

    AST** variable_defenitions;
    size_t variable_defenition_size;
} Scope;

Scope* init_scope();

AST* scope_add_function_definition(Scope* scope, AST* function_definition);
AST* scope_get_function_definition(Scope* scope, const char* name);

AST* scope_add_variable_definition(Scope* scope, AST* variable_definition);
AST* scope_get_variable_definition(Scope* scope, const char* name);


#endif