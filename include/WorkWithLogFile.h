#ifndef WORKWITHLOGFILE_H
#define WORKWITHLOGFILE_H

#include "Akinator.h"

ErrorNumbers openLogFile(FILE** log_file, const char** log_file_name);
ErrorNumbers treeDump(FILE* log_file, TreeElem_t* node);

#endif // WORKWITHLOGFILE_H
