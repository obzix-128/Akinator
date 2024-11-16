#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/Run.h"
#include "../include/AddElement.h"
#include "../include/ReadAndWrite.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers playAkinator(FILE* log_file, const char** database_file_name, TreeElem_t* root)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(database_file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    FILE* database_file = NULL;
    CHECK_ERROR(openFile(&database_file, database_file_name));

    char* answer = (char*) calloc(4, sizeof(char));
    CHECK_NULL_ADDR_ERROR(answer, _CALLOC_ERROR);

    /*CHECK_ERROR(treeRead(database_file, root));*/

    CHECK_ERROR(treeRun(log_file, root, root, answer));

    CHECK_ERROR(treeWrite(database_file, root));

    fclose(database_file);

    CHECK_ERROR(playItAgain(log_file, database_file_name, root, answer));

    free(answer);

    return check_error;
}

ErrorNumbers playItAgain(FILE* log_file, const char** database_file_name, TreeElem_t* root,
                         char* answer)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(database_file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(answer, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(stdout, "Do you want to play more?(yes/no)\n");
    scanf("%3s", answer);

    if(strcmp(answer, "yes") == 0)
    {
        CHECK_ERROR(playAkinator(log_file, database_file_name, root));
    }
    else if(strcmp(answer, "no") == 0)
    {
        fprintf(stdout, "Goodbye\n");
    }
    else
    {
        return _UNIDENTIFINED_RESPONSE_ERROR;
    }

    return check_error;
}

ErrorNumbers treeRun(FILE* log_file, TreeElem_t* node, TreeElem_t* root, char* answer)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(node->left != NULL || node->right != NULL)
    {
        fprintf(stdout, "%s?(yes/no)\n", node->data);

        scanf("%3s", answer);

        if(strcmp(answer, "yes") == 0)
        {
            CHECK_ERROR(treeRun(log_file, node->left, root, answer));
        }
        else if(strcmp(answer, "no") == 0)
        {
            CHECK_ERROR(treeRun(log_file, node->right, root, answer));
        }
        else
        {
            return _UNIDENTIFINED_RESPONSE_ERROR;
        }
    }
    else
    {
        fprintf(stdout, "I think it's %s\n", node->data);
        fprintf(stdout, "Am I right?(yes/no)\n");

        scanf("%3s", answer);

        if(strcmp(answer, "yes") == 0)
        {
            fprintf(stdout, "I knew it.\n");
        }
        else if(strcmp(answer, "no") == 0)
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
