#include "../includes/parser.h"


Parser* init_parser(LEXER* lexer) {
    Parser* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexing(lexer);
    parser->prev_token = parser->current_token;
    parser->scope = init_scope();

    return parser;
}

void parser_eat(Parser* parser, int type) {
    if(parser->current_token->type == type) {
        parser->prev_token = parser->current_token;
        parser->current_token = lexing(parser->lexer);
    } else {
        printf("parser_eat: expected %d got %d on line %d\n", type, parser->current_token->type, parser->current_token->line);
        exit(1);
    }
}

AST* parser_parse(Parser* parser, Scope* scope) {
    return parser_parse_statements(parser, scope);
}

AST* parser_parse_statement(Parser* parser, Scope* scope) {
    switch (parser->current_token->type) {
        case ID:
            return parser_parse_id(parser, scope);
            break;
        case NUMBER:
            return parser_parse_number(parser, scope);
            break;
        
        
    }

    return init_ast(AST_NOOP);
}

AST* parser_parse_statements(Parser* parser, Scope* scope) {
    AST* compound = init_ast(AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
    
    AST* ast_statement = parser_parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;
    
    while (parser->current_token->type == SEMICOLON)
    {
        parser_eat(parser, SEMICOLON);
        AST* ast_statement = parser_parse_statement(parser, scope);
        if(ast_statement){
            compound->compound_size += 1;
            compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT*));
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }
    
    return compound;
    
}

AST* parser_parse_expression(Parser* parser, Scope* scope) {

      AST* ast_left = parser_parse_term(parser, scope);

    
    while (parser->current_token->type == PLUS || parser->current_token->type == MINUS)
    {
        AST* ast_binop = init_ast(AST_BINOP);
        ast_binop->left = ast_left;
        ast_binop->op = parser->current_token->type;
        parser_eat(parser, parser->current_token->type);
        ast_binop->right = parser_parse_expression(parser, scope);
        // printf("left: %d, op: %d, right: %d\n", ast_binop->left->number, ast_binop->op, ast_binop->right->number);

        return ast_binop;
    }
  
    return ast_left;

}

AST* parser_parse_factor(Parser* parser, Scope* scope) {
    switch (parser->current_token->type){
        case STRING:
            return parser_parse_string(parser, scope);
            
        case ID:
            return parser_parse_id(parser, scope);

        case NUMBER:
            return parser_parse_number(parser, scope);
        
    }

    return init_ast(AST_NOOP);
}

AST* parser_parse_term(Parser* parser, Scope* scope) {
    AST* ast_left = parser_parse_factor(parser, scope);

    while (parser->current_token->type == STAR || parser->current_token->type == SLASH )
    {
        AST* ast_binop = init_ast(AST_BINOP);
        ast_binop->left = ast_left;
        ast_binop->op = parser->current_token->type;
        parser_eat(parser, parser->current_token->type);
        ast_binop->right = parser_parse_factor(parser, scope);

        return ast_binop;
    }  

    return ast_left;
}

AST* parser_parse_function_definition(Parser* parser, Scope* scope) {
    AST* function_def = init_ast(AST_FUNCTION_DEFINITION);

    parser_eat(parser, ID);

    char* function_name = parser->current_token->data;
    function_def->function_definition_name = calloc(strlen(function_name) + 1, sizeof(char));
    strcpy(function_def->function_definition_name, function_name);

    parser_eat(parser, ID);

    parser_eat(parser, LPAREN);

    function_def->function_definition_arguments = calloc(1, sizeof(struct AST_STRUCT*));
    AST* ast_argument = parser_parse_variable(parser, scope);
    function_def->function_definition_arguments_size += 1;
    function_def->function_definition_arguments[function_def->function_definition_arguments_size - 1] = ast_argument;

    while (parser->current_token->type == COMMA)
    {
        parser_eat(parser, COMMA);
        function_def->function_definition_arguments_size += 1;
        function_def->function_definition_arguments = realloc(function_def->function_definition_arguments, function_def->function_definition_arguments_size * sizeof(struct AST_STRUCT*));
        AST* ast_argument = parser_parse_variable(parser, scope);
        function_def->function_definition_arguments[function_def->function_definition_arguments_size - 1] = ast_argument;
    }
    
    
    parser_eat(parser, RPAREN);

    parser_eat(parser, LBRACE);

    function_def->function_definition_body = parser_parse_statements(parser, scope);

    parser_eat(parser, RBRACE);
    function_def->scope = scope;
    return function_def;

}

AST* parser_parse_function_call(Parser* parser, Scope* scope) {
    AST* function_call = init_ast(AST_FUNCTION_CALL);
    function_call->function_call_name = parser->prev_token->data;
    parser_eat(parser, LPAREN);
    function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));
    
    AST* ast_expr = parser_parse_expression(parser, scope);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;
    
    while (parser->current_token->type == COMMA)
    {
        parser_eat(parser, COMMA);
        AST* ast_expr = parser_parse_expression(parser, scope);
        function_call->function_call_arguments_size  += 1;
        function_call->function_call_arguments = realloc(function_call->function_call_arguments, function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*));
        function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
    }
    parser_eat(parser, RPAREN);
    function_call->scope = scope;
    return function_call;
}

AST* parser_parse_variable_definition(Parser* parser, Scope* scope) {
    parser_eat(parser, ID);
    char* variable_name = parser->current_token->data;
    parser_eat(parser, ID);
    parser_eat(parser, EQUAL);
    AST* variable_definition_value = parser_parse_expression(parser, scope);
    AST* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_name = variable_name;
    variable_definition->variable_definition_value = variable_definition_value;
    variable_definition->scope = scope;
    return variable_definition;
}

AST* parser_parse_variable(Parser* parser, Scope* scope) {
    char* token_value = parser->current_token->data;
    parser_eat(parser, ID);

    if(parser->current_token->type == LPAREN) {
       return parser_parse_function_call(parser, scope);    
    }
    AST* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;
    ast_variable->scope = scope;
    return ast_variable;


}

AST* parser_parse_string(Parser* parser, Scope* scope) {
    AST* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->data;
    parser_eat(parser, STRING);
    ast_string->scope = scope;
    return ast_string;

}

AST* parser_parse_id(Parser* parser, Scope* scope) {
    if(strcmp(parser->current_token->data, "const") == 0) {
        return parser_parse_variable_definition(parser, scope);
    }if (strcmp(parser->current_token->data, "function") == 0) {
        return parser_parse_function_definition(parser, scope);
    }
    else {
        return parser_parse_variable(parser, scope);
    }
}

AST* parser_parse_number(Parser* parser, Scope* scope) {
    AST* ast_number = init_ast(AST_INT);
    int number = atoi(parser->current_token->data);
    ast_number->number = number;

    parser_eat(parser, NUMBER);
    ast_number->scope = scope;
    return ast_number;
}


