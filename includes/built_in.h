#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "visitor.h"
#include <stdio.h>


AST* builtin_function_print(Visitor* visitor, AST** args, int size);

#endif