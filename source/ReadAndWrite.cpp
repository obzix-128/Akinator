#include "../include/Akinator.h"
#include "../include/ReadAndWrite.h"
#include "../include/ErrorHandler.h"

/*
ErrorNumbers treeRead(FILE* database_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;



    return check_error;
}*/

ErrorNumbers treeWrite(FILE* database_file, TreeElem_t* node)
{
    CHECK_NULL_ADDR_ERROR(database_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

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
