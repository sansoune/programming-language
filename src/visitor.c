#include "../includes/visitor.h"
#include <stdio.h>
#include <string.h>
#include "../includes/built_in.h"





Visitor* init_visitor() {
    Visitor* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variable_defenitions = (void*)0;   
    visitor->variable_defenition_size = 0;

    return visitor;
}


AST* visitor_visist(Visitor* visit, AST* node) {

    switch (node->type)
    {
        case AST_VARIABLE_DEFINITION:
            return visitor_visit_variable_definition(visit, node);
            break;
        case AST_VARIABLE:
            return visitor_visit_variable(visit, node);
            break;
        case AST_INT:
            return visitor_visit_number(visit, node);
            break;
        case AST_STRING:
            return visitor_visit_string(visit, node);
            break;
        case AST_FUNCTION_CALL:
            return visitor_visit_function_call(visit, node);
            break;
        case AST_COMPOUND:
            return visitor_visit_compound(visit, node);
            break;
        case AST_NOOP:
            return node;
            break;

    }

    printf("Unrecognized node type: %d\n", node->type); 

    exit(1);
    return init_ast(AST_NOOP);
}

AST* visitor_visit_variable_definition(Visitor* visit, AST* node) {
    if(visit->variable_defenitions == (void*)0) {
        visit->variable_defenitions = calloc(1, sizeof(struct AST_STRUCT*));
        visit->variable_defenitions[0] = node;
        visit->variable_defenition_size += 1;
    }else {
        visit->variable_defenition_size += 1;
        visit->variable_defenitions = realloc(visit->variable_defenitions,visit->variable_defenition_size * sizeof(struct AST_STRUCT*));
        visit->variable_defenitions[visit->variable_defenition_size - 1] = node;
    }

    return node;
}
AST* visitor_visit_variable(Visitor* visit, AST* node){
    for (int i = 0; i < visit->variable_defenition_size; i++) {
        AST* variable_defenition = visit->variable_defenitions[i];
        if(strcmp(variable_defenition->variable_definition_name, node->variable_name) == 0) {
            return visitor_visist(visit, variable_defenition->variable_definition_value);
        }
    }

    printf("Variable %s not found\n", node->variable_name);
    return node;
}
AST* visitor_visit_function_call(Visitor* visit, AST* node) {

    if(strcmp(node->function_call_name, "print") == 0) {
        return builtin_function_print(visit, node->function_call_arguments, node->function_call_arguments_size);
    }

    printf("undefined function call: %s\n", node->function_call_name);
    exit(1);
}
AST* visitor_visit_string(Visitor* visit, AST* node) {
    return node;
}


AST* visitor_visit_compound(Visitor* visit, AST* node) {
    for(int i = 0; i < node->compound_size; i++) {
        visitor_visist(visit ,node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}

AST* visitor_visit_number(Visitor* visitor, AST* node) {
    return node;
}