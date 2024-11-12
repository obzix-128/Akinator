#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>

typedef int Data_t;

struct TreeElem_t
{
    Data_t data;
    TreeElem_t* left;
    TreeElem_t* right;
};

enum ErrorNumbers{
    _NO_ERROR            = 0,
    _OPEN_ERROR          = 1,
    _NULL_ADDRESS_ERROR  = 2,
    _CALLOC_ERROR        = 3,
    _NUMBER_OF_ARG_ERROR = 4
};

#define CHECK_NULL_ADDR_ERROR(variable, ERROR_NUMBER) if(variable == NULL) \
                                                          {return ERROR_NUMBER;}

#endif // AKINATOR_H
