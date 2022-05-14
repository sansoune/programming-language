#include "../includes/scope.h"
#include <string.h>

Scope* init_scope(){
    Scope* scope = calloc(1, sizeof(struct SCOPE_STRUCT));
    scope->function_definitions = (void*)0;
    scope->function_definitions_size = 0;

    return scope;
}

AST* scope_add_function_definition(Scope* scope, AST* function_definition){
    scope->function_definitions_size += 1;

    if(scope->function_definitions == (void*)0) {
        scope->function_definitions = calloc(1, sizeof(struct AST_STRUCT*));
        // scope->function_definitions[0] = function_definition;
    } else {
        scope->function_definitions = realloc(scope->function_definitions, scope->function_definitions_size * sizeof(struct AST_STRUCT**));
        // scope->function_definitions[scope->function_definitions_size] = function_definition;
    }
    scope->function_definitions[scope->function_definitions_size - 1] = function_definition;
    return function_definition;
}


AST* scope_get_function_definition(Scope* scope, const char* name) {
    for (int i = 0; i < scope->function_definitions_size; i++) {
        AST* function_definition = scope->function_definitions[i];
        if(strcmp(function_definition->function_definition_name, name) == 0) {
            return function_definition;
        }
    }

    return (void*)0;
}