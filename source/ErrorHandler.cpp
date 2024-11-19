#include "../include/ErrorHandler.h"


ErrorNumbers errorHandler(ErrorNumbers error, const char* func_name)
{
    fprintf(stderr, "%s\n", func_name);

    switch(error)
    {
        case _NO_ERROR:
        {
            fprintf(stderr, "No errors were found\n");
            break;
        }
        case _OPEN_ERROR:
        {
            fprintf(stderr, "ERROR: File not open\n");
            break;
        }
        case _NULL_ADDRESS_ERROR:
        {
            fprintf(stderr, "ERROR: a null address was detected\n");
            break;
        }
        case _CALLOC_ERROR:
        {
            fprintf(stderr, "ERROR: calloc\n");
            break;
        }
        case _NUMBER_OF_ARG_ERROR:
        {
            fprintf(stderr, "ERROR: Incorrect number of arguments\n");
            break;
        }
        case _UNIDENTIFINED_RESPONSE_ERROR:
        {
            fprintf(stderr, "ERROR: The entered response was not recognized\n");
            break;
        }
        case _INVALID_ADDRESS_ERROR:
        {
            fprintf(stderr, "ERROR: The address per node has an impossible value\n");
            break;
        }
        case _CHECK_FOUND_ERROR:
        {
            fprintf(stderr, "ERROR: An error was found during the check\n");
            break;
        }
        default:
        {
            fprintf(stderr, "Unknown error\n");
            break;
        }
    }

    return _NO_ERROR;
}
