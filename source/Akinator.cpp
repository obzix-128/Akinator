#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"
#include "../include/CtorAndDtor.h"
#include "../include/Run.h"


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

    struct TreeElem_t root = {};

    CHECK_ERROR(treeCtor(log_file, &root));

    CHECK_ERROR(treeRun(log_file, &root, &root));
    CHECK_ERROR(treeRun(log_file, &root, &root));
    CHECK_ERROR(treeRun(log_file, &root, &root));
    CHECK_ERROR(treeRun(log_file, &root, &root));
    CHECK_ERROR(treeRun(log_file, &root, &root));
    CHECK_ERROR(treeRun(log_file, &root, &root));

    CHECK_ERROR(treeDtor(log_file, &root));

    printf("DONE\n");

    fclose(log_file);

    return check_error;
}
