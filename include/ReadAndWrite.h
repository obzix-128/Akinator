#ifndef READANDWRITE_H
#define READANDWRITE_H

#include "Akinator.h"

ErrorNumbers treeWrite(FILE* database_file, TreeElem_t* node);
ErrorNumbers treeRead(FILE* database_file, TreeElem_t* node);
ErrorNumbers createNewNode(FILE* database_file, TreeElem_t** old_node_lr);
ErrorNumbers searchForOpeningCurlyBrace(FILE* database_file);
ErrorNumbers indentText(FILE* database_file, int size_of_indentation);

#endif // READANDWRITE_H
