#ifndef yass_lexer_h
#define yass_lexer_h

#include "token.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>









Token* lexing(LEXER* lexer);
Token* parse_string(LEXER* lexer);
Token* collect_id(LEXER* lexer);
char* current_char(LEXER* lexer);
uint32_t parse_number(const char* buf);


#endif