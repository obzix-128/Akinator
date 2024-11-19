#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"
#include "../include/CtorAndDtor.h"
#include "../include/Run.h"
#include "../include/ReadAndWrite.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 3;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(_NUMBER_OF_ARG_ERROR, __PRETTY_FUNCTION__);
        return _NUMBER_OF_ARG_ERROR;
    }

    ErrorNumbers check_error = _NO_ERROR;

    FILE* log_file = NULL;
    CHECK_ERROR(openFile(&log_file, argv[1], OPEN_FILE_IN_RECORDING_MODE));
    fprintf(log_file, "<pre>\n");

    struct TreeElem_t root = {};

    CHECK_ERROR(treeCtor(log_file, &root));

    CHECK_ERROR(playAkinator(log_file, argv[2], &root));

    CHECK_ERROR(treeDtor(log_file, &root));

    printf("DONE\n");

    fclose(log_file);

    return check_error;
}
