#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/Run.h"
#include "../include/AddElement.h"


ErrorNumbers treeRun(FILE* log_file, TreeElem_t* node, TreeElem_t* root)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(node->left != NULL || node->right != NULL)
    {
        fprintf(stdout, "%s?\n", node->data);

        char* answer = (char*) calloc(4, sizeof(char));
        scanf("%3s", answer);

        if(strcmp(answer, "yes")) // TODO: изменить
        {
            CHECK_ERROR(treeRun(log_file, node->right, root));
        }
        else if(strcmp(answer, "no")) // TODO: аналогично
        {
            CHECK_ERROR(treeRun(log_file, node->left, root));
        }
        else
        {
            return _UNIDENTIFINED_RESPONSE_ERROR;
        }
    }
    else
    {
        fprintf(stdout, "I think it's %s\n", node->data);

        char* answer = (char*) calloc(4, sizeof(char));
        scanf("%3s", answer);

        if(strcmp(answer, "yes") == 0) // TODO: изменить
        {
            fprintf(stdout, "Goodbye\n");
        }
        else if(strcmp(answer, "no") == 0) // TODO: аналогично
        {
            CHECK_ERROR(treeAddElement(log_file, node, root));
        }
        else
        {
            return _UNIDENTIFINED_RESPONSE_ERROR;
        }
    }

    return check_error;
}
