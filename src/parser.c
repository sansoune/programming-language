#include "../includes/parser.h"


Parser* init_parser(LEXER* lexer) {
    Parser* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexing(lexer);
    parser->prev_token = parser->current_token;

    return parser;
}

void parser_eat(Parser* parser, int type) {
    if(parser->current_token->type == type) {
        parser->prev_token = parser->current_token;
        parser->current_token = lexing(parser->lexer);
    } else {
        printf("parser_eat: expected %d got %d\n", type, parser->current_token->type);
        exit(1);
    }
}

AST* parser_parse(Parser* parser) {
    return parser_parse_statements(parser);
}

AST* parser_parse_statement(Parser* parser) {
    switch (parser->current_token->type) {
        case ID:
            return parser_parse_id(parser);
            break;
        case NUMBER:
            return parser_parse_number(parser);
            break;
        
        
    }

    return init_ast(AST_NOOP);
}

AST* parser_parse_statements(Parser* parser) {
    AST* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
    
    AST* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;
    
    while (parser->current_token->type == SEMICOLON)
    {
        parser_eat(parser, SEMICOLON);
        AST* ast_statement = parser_parse_statement(parser);
        if(ast_statement){
            compound->compound_size += 1;
            compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT*));
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }
    
    return compound;
    
}

AST* parser_parse_expression(Parser* parser) {

    return parser_parse_term(parser);

}

AST* parser_parse_factor(Parser* parser) {
    switch (parser->current_token->type){
        case STRING:
            return parser_parse_string(parser);
            
        case ID:
            return parser_parse_id(parser);

        case NUMBER:
            return parser_parse_number(parser);
        
    }

    return init_ast(AST_NOOP);
}

AST* parser_parse_term(Parser* parser) {
    AST* ast_left = parser_parse_factor(parser);
    while (parser->current_token->type == PLUS) {
        parser_eat(parser, parser->current_token->type);
        AST* ast_binop = init_ast(AST_BINOP);
        ast_binop->left = ast_left;
        ast_binop->op = parser->current_token->type;
        ast_binop->right = parser_parse_expression(parser);
        return ast_binop;
    }
    return ast_left;
}

AST* parser_parse_function_call(Parser* parser) {
    AST* function_call = init_ast(AST_FUNCTION_CALL);
    function_call->function_call_name = parser->prev_token->data;
    parser_eat(parser, LPAREN);
    function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));
    
    AST* ast_expr = parser_parse_expression(parser);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;
    
    while (parser->current_token->type == COMMA)
    {
        parser_eat(parser, COMMA);
        AST* ast_expr = parser_parse_expression(parser);
        function_call->function_call_arguments_size  += 1;
        function_call->function_call_arguments = realloc(function_call->function_call_arguments, function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*));
        function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
    }
    parser_eat(parser, RPAREN);

    return function_call;
}

AST* parser_parse_variable_definition(Parser* parser) {
    parser_eat(parser, ID);
    char* variable_name = parser->current_token->data;
    parser_eat(parser, ID);
    parser_eat(parser, EQUAL);
    AST* variable_definition_value = parser_parse_expression(parser);
    AST* variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_name = variable_name;
    variable_definition->variable_definition_value = variable_definition_value;
    return variable_definition;
}

AST* parser_parse_variable(Parser* parser) {
    char* token_value = parser->current_token->data;
    parser_eat(parser, ID);

    if(parser->current_token->type == LPAREN) {
       return parser_parse_function_call(parser);    
    }
    AST* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;
    return ast_variable;


}

AST* parser_parse_string(Parser* parser) {
    AST* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->data;
    parser_eat(parser, STRING);
    return ast_string;

}

AST* parser_parse_id(Parser* parser) {
    if(strcmp(parser->current_token->data, "const") == 0) {
        return parser_parse_variable_definition(parser);
    }else {
        return parser_parse_variable(parser);
    }
}

AST* parser_parse_number(Parser* parser) {
    AST* ast_number = init_ast(AST_INT);
    int number = atoi(parser->current_token->data);
    ast_number->number = number;

    parser_eat(parser, NUMBER);
    return ast_number;
}


