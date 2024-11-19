#include "../include/WorkWithLogFile.h"
#include "../include/ErrorHandler.h"


ErrorNumbers openFile(FILE** file, const char* file_name, const char* opening_mode)
{
    CHECK_NULL_ADDR_ERROR(file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_name, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(opening_mode, _NULL_ADDRESS_ERROR);

    *file = fopen(file_name, opening_mode);
    CHECK_NULL_ADDR_ERROR(*file, _OPEN_ERROR);

    return _NO_ERROR;
}

ErrorNumbers treeDump(FILE* log_file, TreeElem_t* root, const char* func_name,
                      TreeElem_t* new_node)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(func_name, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error;

    fprintf(log_file, "<h2>Dump is called from the function %s </h2>\n", func_name);

    fprintf(log_file, "root = [%p]\n", root);
    fprintf(log_file, "root->data = %s? [%p]\n", root->data, &root->data);
    fprintf(log_file, "root->left = [%p]\n", root->left);
    fprintf(log_file, "root->right = [%p]\n", root->right);
    fprintf(log_file, "\n");

    CHECK_ERROR(buildGraf(log_file, root, new_node));

    return check_error;
}

ErrorNumbers buildGraf(FILE* log_file, TreeElem_t* node, TreeElem_t* new_node)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    static int counter = 0;

    const int FILE_NAME_SIZE = 100;
    char file_name[FILE_NAME_SIZE] = {};
    char command[FILE_NAME_SIZE] = {};

    sprintf(file_name, "image/Graf%d.txt", counter);

    FILE* file_to_write = NULL;
    CHECK_ERROR(openFile(&file_to_write, file_name, OPEN_FILE_IN_RECORDING_MODE));

    fprintf(file_to_write, "digraph\n");
    fprintf(file_to_write, "{\n");

    fprintf(file_to_write, "rankdir = TB;\n");

    fprintf(file_to_write, "{\n");

    CHECK_ERROR(buildAllNodes(node, file_to_write, new_node));

    fprintf(file_to_write, "}\n");

    fprintf(file_to_write, "}\n");

    fclose(file_to_write);

    sprintf(file_name, "image/Graf%d", counter);

    fprintf(log_file, "<img src = \"%s.png\" width = \"1400\">", file_name);

    sprintf(command, "dot %s.txt -T png -o %s.png", file_name, file_name);

    system(command);

    counter += 1;

    return check_error;
}

ErrorNumbers buildAllNodes(TreeElem_t* node, FILE* file_to_write, TreeElem_t* new_node)
{
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(node->left != 0)
    {
        CHECK_ERROR(buildAllNodes(node->left, file_to_write, new_node));
    }
    if(node->right != 0)
    {
        CHECK_ERROR(buildAllNodes(node->right, file_to_write, new_node));
    }

    fprintf(file_to_write, "_%p[shape = record, style = \"filled\" fillcolor = \"", node);

    if(new_node == node)
    {
        fprintf(file_to_write, "#b0ffb0");
    }
    else
    {
        fprintf(file_to_write, "#bbffff");
    }

    if(node->left != NULL || node->right != NULL)
    {
        fprintf(file_to_write, "\", label = \" { address = %p | data = %s? | {", node, node->data);
    }
    else
    {
        fprintf(file_to_write, "\", label = \" { address = %p | data = %s | {", node, node->data);
    }

    if(node->left != NULL)
    {
        fprintf(file_to_write, " <_l_%p> left = %p |", node->left, node->left);
    }
    else
    {
        fprintf(file_to_write, " left = NULL |");
    }

    if(node->right != NULL)
    {
        fprintf(file_to_write, " <_r_%p> right = %p }} \"]\n", node->right, node->right);
    }
    else
    {
        fprintf(file_to_write, " right = NULL }} \"]\n");
    }

    if(node->left != NULL)
    {
        fprintf(file_to_write, "_%p:<_l_%p>->_%p[label = \"Yes\"]\n", node, node->left, node->left);
    }
    if(node->right != NULL)
    {
        fprintf(file_to_write, "_%p:<_r_%p>->_%p[label = \"No\"]\n", node, node->right, node->right);
    }

    return check_error;
}
