#ifndef parser_h
#define parser_h

#include "lexer.h"
#include "AST.h"
#include "scope.h"

typedef struct PARSER_STRUCT {
    LEXER* lexer;
    Token* current_token;
    Token* prev_token;
    Scope* scope;
} Parser;

Parser* init_parser(LEXER* lexer);
void parser_eat(Parser* parser, int type);
AST* parser_parse(Parser* parser, Scope* scope);
AST* parser_parse_statement(Parser* parser, Scope* scope);
AST* parser_parse_statements(Parser* parser, Scope* scope);
AST* parser_parse_expression(Parser* parser, Scope* scope);
AST* parser_parse_factor(Parser* parser, Scope* scope);
AST* parser_parse_term(Parser* parser, Scope* scope);
AST* parser_parse_function_call(Parser* parser, Scope* scope);
AST* parser_parse_function_definition(Parser* parser, Scope* scope);
AST* parser_parse_variable(Parser* parser, Scope* scope);
AST* parser_parse_variable_definition(Parser* parser, Scope* scope);
AST* parser_parse_string(Parser* parser, Scope* scope);
AST* parser_parse_id(Parser* parser, Scope* scope);
AST* parser_parse_number(Parser* parser, Scope* scope);

#endif