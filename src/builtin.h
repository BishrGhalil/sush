/* builtin.h -- header file for builtin.c.

   This file is part of SuSh, A Shell that Sucks less.  SuSh is free
   software; no one can prevent you from reading the source code, or
   giving it to someone else.  This file is copyrighted under the GNU
   General Public License.

   Copyright (C) 2021 Bishr Ghalil.

   This file is part of SuSh.

   SuSh is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY.  No author or distributor accepts responsibility to
   anyone for the consequences of using it or for whether it serves
   any particular purpose or works at all.

   Everyone is granted permission to copy, modify and redistribute
   SuSh, but only under the conditions described in the GNU General
   Public License.

  Initial author: Bishr Ghalil
*/
#ifndef BUILTIN_H_
#define BUILTIN_H_

#include <stdlib.h>
#include "hashtable.h"

#define TOK_BFRSIZE 64
#define COMMAND_SIZE 1024
#define TOK_DELIM " \t\r\n\a"

extern ht_table *ht;
extern char prev_wd[1024];

char **parser(char *line);

void ht_init();
int cmd_cd(char **args);
int cmd_help(char **args);
int cmd_history(char **args);
int cmd_exit(char **args);

char *prompt();

int sysexec(char **args);
int execute(char **args);

#endif
