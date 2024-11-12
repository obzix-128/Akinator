#include "../include/WorkWithLogFile.h"
#include "../include/ErrorHandler.h"


ErrorNumbers openLogFile(FILE** log_file, const char** log_file_name)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(log_file_name, _NULL_ADDRESS_ERROR);

    *log_file = fopen(*log_file_name, "w");
    CHECK_NULL_ADDR_ERROR(*log_file, _OPEN_ERROR);

    fprintf(*log_file, "<pre>\n");

    return _NO_ERROR;
}

ErrorNumbers treeDump(FILE* log_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(log_file, "(");
    if(node->left != 0)
    {
        CHECK_ERROR(treeDump(log_file, node->left));
    }
    fprintf(log_file, "%d", node->data);
    if(node->right != 0)
    {
        CHECK_ERROR(treeDump(log_file, node->right));
    }

    fprintf(log_file, ")");

    return check_error;
}
