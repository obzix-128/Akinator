#ifndef RUN_H
#define RUN_H

ErrorNumbers treeRun(FILE* log_file, TreeElem_t* node, TreeElem_t* root, char* answer);
ErrorNumbers playAkinator(FILE* log_file, const char** database_file_name, TreeElem_t* root);
ErrorNumbers playItAgain(FILE* log_file, const char** database_file_name, TreeElem_t* root,
                         char* answer);
                         
#endif // RUN_H
