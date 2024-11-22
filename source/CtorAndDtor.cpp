#include "../include/CtorAndDtor.h"
#include "../include/ErrorHandler.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers treeCtor(FILE* log_file, TreeElem_t* root)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root,     _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    const char* ROOT_ANSWER = "It is unknown what";
    root->data = (char*) calloc(_DATA_SIZE_, sizeof(char));
    CHECK_NULL_ADDR_ERROR(root->data, _CALLOC_ERROR);

    strncpy(root->data, ROOT_ANSWER, _DATA_SIZE_);

    root->left   = NULL;
    root->right  = NULL;

    CHECK_ERROR(treeDump(log_file, root, __PRETTY_FUNCTION__, root));

    return check_error;
}

ErrorNumbers treeDtor(FILE* log_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,     _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(node->left != 0)
    {
        CHECK_ERROR(treeDtor(log_file, node->left));
    }
    if(node->right != 0)
    {
        CHECK_ERROR(treeDtor(log_file, node->right));
    }

    free(node->data);
    node->data  = NULL;
    node->left  = NULL;
    node->right = NULL;
    free(node);

    return check_error;
}
