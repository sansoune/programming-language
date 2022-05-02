#include "../includes/parser.h"


Parser* init_parser(LEXER* lexer) {
    Parser* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexing(lexer);

    return parser;
}

void parser_eat(Parser* parser, int type) {
    if(parser->current_token->type == type) {
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
        
        
    }
}

AST* parser_parse_statements(Parser* parser) {
    AST* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
    
    AST* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    
    while (parser->current_token->type == SEMICOLON)
    {
        parser_eat(parser, SEMICOLON);
        AST* ast_statement = parser_parse_statement(parser);
        compound->compound_size += 1;
        compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT*));
        compound->compound_value[compound->compound_size - 1] = ast_statement;
    }
    
    return compound;
    
}

AST* parser_parse_expression(Parser* parser) {

    switch (parser->current_token->type){
        case STRING:
            return parser_parse_string(parser);
            break;
    }

}

AST* parser_parse_factor(Parser* parser) {

}

AST* parser_parse_term(Parser* parser) {

}

AST* parser_parse_function_call(Parser* parser) {

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


