#include "../include/ErrorHandler.h"
#include "../include/Run.h"
#include "../include/AddElement.h"
#include "../include/ReadAndWrite.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers playAkinator(FILE* log_file, const char* database_file_name, TreeElem_t* root)
{
    CHECK_NULL_ADDR_ERROR(log_file,           _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(database_file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root,               _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    FILE* database_file = NULL;
    CHECK_ERROR(openFile(&database_file, database_file_name, OPEN_FILE_IN_READ_MODE));

    const int _ANSWER_SIZE_ = 32;
    char* answer = (char*) calloc(_ANSWER_SIZE_, sizeof(char));
    CHECK_NULL_ADDR_ERROR(answer, _CALLOC_ERROR);

    CHECK_ERROR(treeRead(database_file, root));
    fclose(database_file);
    CHECK_ERROR(treeDump(log_file, root, __PRETTY_FUNCTION__, NULL));

    CHECK_ERROR(selectMode(answer));

    if(strcmp(answer, "play") == 0) // TODO? define
    {
        CHECK_ERROR(playMode(log_file, database_file_name, root, answer));
    }
    else if(strcmp(answer, "definition") == 0)
    {
        CHECK_ERROR(definitionMode(root, answer));
    }
    else if(strcmp(answer, "comparison") == 0)
    {
       /* CHECK_ERROR();*/
    }

    CHECK_ERROR(playItAgain(log_file, database_file_name, root, answer));

    free(answer);

    return check_error;
}

ErrorNumbers definitionMode(TreeElem_t* root, char* answer)
{
    CHECK_NULL_ADDR_ERROR(root,   _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(answer, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(stdout, "Enter a word and I'll define it.\n");
    scanf("%" _ANSWER_SIZE "s", answer);

    struct StackInfo stack_with_path = {};

    CHECK_ERROR(StackCtor(&stack_with_path));

    bool check_the_availability_in_the_database = false;
    CHECK_ERROR(findWordInTree(root, &answer, &check_the_availability_in_the_database,
                                &stack_with_path));

    CHECK_ERROR(giveDefinition(&stack_with_path));

    CHECK_ERROR(StackDtor(&stack_with_path));
    if(check_the_availability_in_the_database == false)
    {
        fprintf(stdout, "There is no such word in the database.\n");
    }

    return check_error;
}

ErrorNumbers playMode(FILE* log_file, const char* database_file_name, TreeElem_t* root, char* answer)
{
    CHECK_NULL_ADDR_ERROR(log_file,           _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(database_file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root,               _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(answer,             _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    FILE* database_file = NULL;

    CHECK_ERROR(treeRun(log_file, root, root, answer));

    CHECK_ERROR(openFile(&database_file, database_file_name, OPEN_FILE_IN_RECORDING_MODE));
    CHECK_ERROR(treeWrite(database_file, root));

    fclose(database_file);

    return check_error;
}

ErrorNumbers selectMode(char* answer)
{
    CHECK_NULL_ADDR_ERROR(answer, _NULL_ADDRESS_ERROR);

    fprintf(stdout, "If you want me to guess something, enter \"play\",\n"
                    "if you want me to define a thing, enter \"definition\",\n"
                    "if you want me to compare two things, enter \"comparison\".\n");

    scanf("%" _ANSWER_SIZE "s", answer);

    return _NO_ERROR;
}

ErrorNumbers giveDefinition(StackInfo* stack_with_path)
{
    CHECK_NULL_ADDR_ERROR(stack_with_path, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    struct TreeElem_t* previous_node = NULL;
    CHECK_ERROR(StackPop(stack_with_path, &previous_node));
    fprintf(stdout, "%s: ", previous_node->data);

    char* node_data_address = previous_node->data;

    do
    {
        CHECK_ERROR(StackPop(stack_with_path, &previous_node));

        if(node_data_address == previous_node->left->data)
        {
            fprintf(stdout, "%s, ", previous_node->data);
        }
        else if(node_data_address == previous_node->right->data)
        {
            fprintf(stdout, "not %s, ", previous_node->data);
        }
        else
        {
            return _INVALID_ADDRESS_ERROR;
        }

        node_data_address = previous_node->data;
    }
    while(stack_with_path->size > 0);

    fprintf(stdout, "\n");

    return check_error;
}

ErrorNumbers findWordInTree(TreeElem_t* node, char** answer,
                            bool* check_the_availability_in_the_database, StackInfo* stack_with_path)
{
    CHECK_NULL_ADDR_ERROR(node,                                   _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(answer,                                 _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(*answer,                                _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(check_the_availability_in_the_database, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(stack_with_path,                        _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(*check_the_availability_in_the_database == false)
    {
        CHECK_ERROR(StackPush(stack_with_path, node));
    }

    if(node->left != 0)
    {
        CHECK_ERROR(findWordInTree(node->left, answer, check_the_availability_in_the_database,
                                   stack_with_path));
    }
    if(node->right != 0)
    {
        CHECK_ERROR(findWordInTree(node->right, answer, check_the_availability_in_the_database,
                                   stack_with_path));
    }

    if(strcmp(*answer, node->data) == 0)
    {
        *check_the_availability_in_the_database = true;
    }
    else if(*check_the_availability_in_the_database == false)
    {
        CHECK_ERROR(StackPop(stack_with_path, &node));
    }

    return check_error;
}

ErrorNumbers playItAgain(FILE* log_file, const char* database_file_name, TreeElem_t* root,
                         char* answer)
{
    CHECK_NULL_ADDR_ERROR(log_file,           _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(database_file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root,               _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(answer,             _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(stdout, "Do you want to play more?(yes/no)\n");
    scanf("%" _ANSWER_SIZE "s", answer);

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
    CHECK_NULL_ADDR_ERROR(node,     _NULL_ADDRESS_ERROR);

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
