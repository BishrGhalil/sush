/* builtin.c -- builtin functions execution and management

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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>

#include "builtin.h"
#include "hashtable.h"

char prev_wd[COMMAND_SIZE];
ht_table *ht; // built in commands hashtable

void ht_init()
{
    ht = ht_new();
    ht_insert(ht, "cd", "change the current directory", &cmd_cd);
    ht_insert(ht, "help", "print this help message", &cmd_help);
    ht_insert(ht, "history", "print commands history", &cmd_history);
    ht_insert(ht, "exit", "exit sush", &cmd_exit);
}

// Builtin function implementations.
int cmd_cd(char **args)
{
    if (args[1] == NULL) {
	char *home = getenv("HOME");
	args[1] = (char *) malloc(sizeof(home));
	strcpy(args[1], home);
	cmd_cd(args);
	free(args[1]);
    }
    else if (strcmp(args[1], "-") == 0) {
	if (sizeof(args[1]) < sizeof(prev_wd)){
	    args[1] = malloc(sizeof(prev_wd));
	}
	strcpy(args[1], prev_wd);
	printf("%s\n", prev_wd);
	cmd_cd(args);
    } else {
	getcwd(prev_wd, sizeof(prev_wd));
        if (chdir(args[1]) != 0) {
            perror("sush");
        }
    }
    return 1;
}

int cmd_help(char **args)
{
    printf("Bishr Ghalil CSH\n\n");
    printf("Built in commands\n");

    for (int i = 0; i < ht->count; i++){
        printf("    %-20s\t%s\n", ht->items[i]->key, ht->items[i]->helpmsg);
    }

    return 1;
}

int cmd_history(char **args)
{
    HISTORY_STATE *myhist = history_get_history_state ();

    HIST_ENTRY **mylist = history_list ();

    printf ("\nhistory session for %s\n\n", getenv("USER"));
    for (int i = 0; i < myhist->length; i++) {
        printf ("%.3d %-20s%s\n", i + 1, mylist[i]->line, mylist[i]->timestamp);
    }

    putchar ('\n');
    return 1;
}

int cmd_exit(char **args)
{
        printf("exit\n");
        return 0;
}

int sysexec(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("sush");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("sush");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int execute(char **args)
{
        int j = 0;
    if (args[0] == NULL) {
        return 1;
    }

    if (ht_search(ht, args[0])) {
	return ht_run_func(ht, args[0], args);
    } else {
	return sysexec(args);
    }
}

char **parser(char *line)
{
    int bfrsize = TOK_BFRSIZE, cursor = 0;
    char **tokens = malloc(bfrsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "sush: allocation error\n");
	exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[cursor] = token;
        cursor++;

        if (cursor >= bfrsize) {
            bfrsize += TOK_BFRSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bfrsize * sizeof(char*));
            if (!tokens) {
		free(tokens_backup);
                fprintf(stderr, "sush: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[cursor] = NULL;
    return tokens;
}
