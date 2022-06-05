#include "../includes/visitor.h"
#include <stdio.h>
#include <string.h>
#include "../includes/built_in.h"
#include "../includes/scope.h"
#include "../includes/math.h"





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
        case AST_BINOP:
            return visitor_visit_binop(visit, node);
            break;
        case AST_FUNCTION_DEFINITION:
            return visitor_visit_function_definition(visit, node);
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

AST* visitor_visit_function_definition(Visitor* visit,AST* node) {
    scope_add_function_definition(node->scope, node);
    return node;
}

AST* visitor_visit_function_call(Visitor* visit, AST* node) {

    if(strcmp(node->function_call_name, "print") == 0) {
        return builtin_function_print(visit, node->function_call_arguments, node->function_call_arguments_size);
    }

    AST* fdef = scope_get_function_definition(node->scope, node->function_call_name);
    if(fdef != (void*)0) {
        return visitor_visist(visit, fdef->function_definition_body);
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

AST* visitor_visit_binop(Visitor* visit, AST* node) {
    AST* new_binop = init_ast(AST_BINOP);
    new_binop->left = visitor_visist(visit, node->left);
    new_binop->op = node->op;
    new_binop->right = visitor_visist(visit, node->right);
    // printf("num1:%d op:%d num2:%d\n", new_binop->left->number, new_binop->op, new_binop->right->number);

    if(new_binop->op == 9){
        new_binop->left->number = add(new_binop->left->number, new_binop->right->number);
    }
    if(new_binop->op == 10){
        // new_binop->right->number *= -1;
        new_binop->left->number -= new_binop->right->number;
        // new_binop->left->number = add(new_binop->left->number, new_binop->right->number);
    }
    if(new_binop->op == 12){
        new_binop->left->number *= new_binop->right->number;
    }
    if(new_binop->op == 15){
        new_binop->left->number /= new_binop->right->number;
    }
    
    AST* result = init_ast(AST_INT);
    result->number = new_binop->left->number;

    return result;
}