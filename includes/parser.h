#ifndef parser_h
#define parser_h

#include "lexer.h"
#include "AST.h"
typedef struct PARSER_STRUCT {
    LEXER* lexer;
    Token* current_token;
} Parser;

Parser* init_parser(LEXER* lexer);
void parser_eat(Parser* parser, int type);
AST* parser_parse(Parser* parser);
AST* parser_parse_statement(Parser* parser);
AST* parser_parse_statements(Parser* parser);
AST* parser_parse_expression(Parser* parser);
AST* parser_parse_factor(Parser* parser);
AST* parser_parse_term(Parser* parser);
AST* parser_parse_function_call(Parser* parser);
AST* parser_parse_variable(Parser* parser);
AST* parser_parse_variable_definition(Parser* parser);
AST* parser_parse_string(Parser* parser);
AST* parser_parse_id(Parser* parser);

#endif