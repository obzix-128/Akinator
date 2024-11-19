#ifndef PUSHANDPOP_H
#define PUSHANDPOP_H

#include "../include/Main.h"

#include <stdlib.h>

ErrorNumbers StackPush(StackInfo* my_stack, StackElem_t element_value);
ErrorNumbers StackPop (StackInfo* my_stack, StackElem_t* element_value);

ErrorNumbers StackMemory(StackInfo* my_stack);

#endif // PUSHANDPOP_H
