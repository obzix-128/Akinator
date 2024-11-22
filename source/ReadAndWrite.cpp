#include "../include/ReadAndWrite.h"
#include "../include/ErrorHandler.h"


ErrorNumbers treeRead(FILE* database_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fscanf(database_file, "{\"%" _DATA_SIZE "[^\"]\"", node->data);

    char check_next_letter = 0;

    fscanf(database_file, "%c", &check_next_letter);
    if(check_next_letter == '}')
    {
        return check_error;
    }

    CHECK_ERROR(createNewNode(database_file, &node->left));
    CHECK_ERROR(createNewNode(database_file, &node->right));

    return check_error;
}

ErrorNumbers createNewNode(FILE* database_file, TreeElem_t** old_node_lr) // TODO? left/right - lr
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    struct TreeElem_t* new_node = (TreeElem_t*) calloc(1, sizeof(TreeElem_t));
    CHECK_NULL_ADDR_ERROR(new_node, _CALLOC_ERROR);

    CHECK_ERROR(searchForOpeningCurlyBrace(database_file));

    new_node->data = (char*) calloc(_DATA_SIZE_, sizeof(char));
    CHECK_NULL_ADDR_ERROR(new_node->data, _CALLOC_ERROR);
    *old_node_lr = new_node;
    CHECK_ERROR(treeRead(database_file, new_node));

    return check_error;
}

ErrorNumbers searchForOpeningCurlyBrace(FILE* database_file)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);

    char check_next_letter = 0;

    while(check_next_letter != '{')
    {
        fscanf(database_file, "%c", &check_next_letter);
    }

    const int STEP_BACK = -1;

    fseek(database_file, STEP_BACK, SEEK_CUR);

    return _NO_ERROR;
}

ErrorNumbers treeWrite(FILE* database_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    static int size_of_indentation = -1; // So that the first indentation is 0

    fprintf(database_file, "{");
    fprintf(database_file, "\"%s\"", node->data);
    size_of_indentation += 1;

    if(node->left != 0)
    {
        fprintf(database_file, "\n");
        CHECK_ERROR(indentText(database_file, size_of_indentation));

        fprintf(database_file, "yes:");
        CHECK_ERROR(treeWrite(database_file, node->left));
    }
    if(node->right != 0)
    {
        fprintf(database_file, "no: ");
        CHECK_ERROR(treeWrite(database_file, node->right));
    }

    fprintf(database_file, "}\n");
    size_of_indentation -= 1;
    CHECK_ERROR(indentText(database_file, size_of_indentation));

    return check_error;
}

ErrorNumbers indentText(FILE* database_file, int size_of_indentation)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);

    for(int i = 0; i < size_of_indentation; i++)
    {
        fprintf(database_file, "    ");
    }

    return _NO_ERROR;
}
