#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeElem_t
{
    char* data;
    TreeElem_t* left;
    TreeElem_t* right;
};

enum ErrorNumbers{
    _NO_ERROR                     = 0,
    _OPEN_ERROR                   = 1,
    _NULL_ADDRESS_ERROR           = 2,
    _CALLOC_ERROR                 = 3,
    _NUMBER_OF_ARG_ERROR          = 4,
    _UNIDENTIFINED_RESPONSE_ERROR = 5,
    _INVALID_ADDRESS_ERROR        = 6,
    _CHECK_FOUND_ERROR            = 7
};

#define CHECK_NULL_ADDR_ERROR(variable, ERROR_NUMBER) if(variable == NULL) \
                                                          {return ERROR_NUMBER;}

const int _DATA_SIZE_ = 32;
#define _DATA_SIZE "31"

#endif // AKINATOR_H
