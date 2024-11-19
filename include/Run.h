#ifndef RUN_H
#define RUN_H

#include <stdbool.h>
#include "Akinator.h"

#include "../Stack/include/Main.h"
#include "../Stack/include/CtorAndDtor.h"
#include "../Stack/include/PushAndPop.h"
#include "../Stack/include/Verificator.h"
#include "../Stack/include/Dump.h"

ErrorNumbers treeRun(FILE* log_file, TreeElem_t* node, TreeElem_t* root, char* answer);
ErrorNumbers playAkinator(FILE* log_file, const char* database_file_name, TreeElem_t* root);
ErrorNumbers playItAgain(FILE* log_file, const char* database_file_name, TreeElem_t* root,
                         char* answer);
ErrorNumbers giveDefinition(TreeElem_t* node, char** answer,
                            bool* check_the_availability_in_the_database, StackInfo* stack_with_path);

#endif // RUN_H
