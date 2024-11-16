#ifndef WORKWITHLOGFILE_H
#define WORKWITHLOGFILE_H

#include "Akinator.h"

ErrorNumbers openFile(FILE** file, const char** file_name);
ErrorNumbers treeDump(FILE* log_file, TreeElem_t* root, const char* func_name,
                      TreeElem_t* new_node);
ErrorNumbers buildGraf(FILE* log_file, TreeElem_t* node, TreeElem_t* new_node);
ErrorNumbers buildAllNodes(TreeElem_t* node, FILE* file_to_write, TreeElem_t* new_node);

#endif // WORKWITHLOGFILE_H
