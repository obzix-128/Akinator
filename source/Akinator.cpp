#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"
#include "../include/AddElements.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 2;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_NUMBER_OF_ARG_ERROR, __PRETTY_FUNCTION__);
        return _NUMBER_OF_ARG_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    FILE* log_file = NULL;
    CHECK_ERROR(openLogFile(&log_file, &argv[1]));

    struct TreeElem_t root = {50, NULL, NULL};

    struct TreeElem_t second = {70, NULL, NULL};
    struct TreeElem_t third = {60, NULL, NULL};

    struct TreeElem_t first = {20, NULL, NULL};
    struct TreeElem_t fourth = {40, NULL, NULL};
    struct TreeElem_t fifth = {30, NULL, NULL};
    struct TreeElem_t sixth = {10, NULL, NULL};

    root.left = &first;
    root.right = &second;

    second.left = &third;

    first.left = &sixth;
    first.right = &fifth;

    fifth.right = &fourth;

    CHECK_ERROR(addElement(log_file, &root, 25));

    CHECK_ERROR(treeDump(log_file, &root));

    printf("DONE\n");

    fclose(log_file);

    return check_error;
}
