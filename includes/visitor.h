#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"

typedef struct VISITOR_STRUCT {
    
} Visitor; 

Visitor* init_visitor();

AST* visitor_visist(Visitor* visit, AST* node);

AST* visitor_visit_variable_definition(Visitor* visit, AST* node);
AST* visitor_visit_variable(Visitor* visit,AST* node);
AST* visitor_visit_function_call(Visitor* visit, AST* node);
AST* visitor_visit_function_definition(Visitor* visit,AST* node);
AST* visitor_visit_string(Visitor* visit, AST* node);
AST* visitor_visit_binop(Visitor* visit, AST* node);
AST* visitor_visit_compound(Visitor* visit, AST* node);
AST* visitor_visit_number(Visitor* visit, AST* node);


#endif