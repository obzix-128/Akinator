#include "../include/AddElements.h"
#include "../include/ErrorHandler.h"


ErrorNumbers addElement(FILE* log_file, TreeElem_t* node, Data_t value)
{
    CHECK_NULL_ADDR_ERROR(log_file, _NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = _NO_ERROR;

    if(value > node->data)
    {
        if(node->right == NULL)
        {
            TreeElem_t* new_node = (TreeElem_t*) calloc(1, sizeof(TreeElem_t));
            new_node->data = value;
            node->right = new_node;

            return check_error;
        }
        else
        {
            CHECK_ERROR(addElement(log_file, node->right, value));

            return check_error;
        }
    }

    if(value <= node->data)
    {
        if(node->left == NULL)
        {
            TreeElem_t* new_node = (TreeElem_t*) calloc(1, sizeof(TreeElem_t));
            new_node->data = value;
            node->left = new_node;

            return check_error;
        }
        else
        {
            CHECK_ERROR(addElement(log_file, node->left, value));

            return check_error;
        }
    }

    return check_error;
}
