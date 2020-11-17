#include "headers.h"

#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "fgbg.h"
#include "history.h"
#include "redirect.h"
#include "setenv.h"
#include "unsetenv.h"
#include "kjob.h"
#include "overkill.h"
#include "bg.h"
#include "fg.h"
#include "jobs.h"

#ifndef __EXECUTE_H
#define __EXECUTE_H

int tokenize(char str[]);
void execute(char cmd[]);

#endif // __EXECUTE_H