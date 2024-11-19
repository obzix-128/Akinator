#ifndef VERIFICATOR_H
#define VERIFICATOR_H
#include "../include/Main.h"

ErrorNumbers StackVerificator(StackInfo* my_stack);

#define STACK_VERIFICATOR if(StackVerificator(my_stack)) return StackVerificator(my_stack);

#endif // VERIFICATOR_H
