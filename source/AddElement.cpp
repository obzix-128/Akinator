#include "../include/Akinator.h"
#include "../include/ErrorHandler.h"
#include "../include/AddElement.h"
#include "../include/WorkWithLogFile.h"


ErrorNumbers treeAddElement(FILE* log_file, TreeElem_t* node, TreeElem_t* root)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    fprintf(stdout, "What did you wish for?\n");

    TreeElem_t* new_node = (TreeElem_t*) calloc(1, sizeof(TreeElem_t));
    CHECK_NULL_ADDR_ERROR(new_node, _CALLOC_ERROR);

    TreeElem_t* old_node = (TreeElem_t*) calloc(1, sizeof(TreeElem_t));
    CHECK_NULL_ADDR_ERROR(old_node, _CALLOC_ERROR);

    new_node->data = (char*) calloc(32, sizeof(char)); // TODO: Переделать
    CHECK_NULL_ADDR_ERROR(new_node->data, _CALLOC_ERROR);

    old_node->data = (char*) calloc(32, sizeof(char)); // TODO: Переделать
    CHECK_NULL_ADDR_ERROR(new_node->data, _CALLOC_ERROR);

    scanf(" %[^\n]", new_node->data); // TODO: &

    strncpy(old_node->data, node->data, 32); // TODO: &

    node->right = old_node;
    node->left  = new_node;

    fprintf(stdout, "How does %s differ from %s?\n", new_node->data, old_node->data);

    scanf(" %[^\n]", node->data);

    CHECK_ERROR(treeDump(log_file, root, __PRETTY_FUNCTION__, new_node));

    return check_error;
}
