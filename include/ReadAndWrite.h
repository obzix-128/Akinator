#ifndef READANDWRITE_H
#define READANDWRITE_H

ErrorNumbers treeWrite(FILE* database_file, TreeElem_t* node);
/*ErrorNumbers treeRead(FILE* database_file, TreeElem_t* node);*/
ErrorNumbers indentText(FILE* database_file, int size_of_indentation);

#endif // READANDWRITE_H
