#ifndef SHELL_H
#define SHELL_H

// Standard library includes
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXIMUM_LINE_LENGTH 1024
typedef unsigned long long u64;

// Project includes
#include "prompt.h"
#include "input.h"
#include "tokenizer.h"
#include "executor.h"
#include "builtins.h"
#include "cmdHistory.h"
#endif