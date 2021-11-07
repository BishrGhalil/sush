/* shell.c -- the main shell filei

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
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "builtin.h"

void 
shell_loop(void)
{
    char *shell_prompt;
    char *line;
    char **args;
    int status = 1;

    while(status) {
	shell_prompt = prompt();
	line = readline(shell_prompt);
	args = parser(line);
	status = execute(args);

	free(line);
	free(args);
	free(shell_prompt);
    }

}

void
sighandler(int sig)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    return;
}

int
main(int argc, char **argv)
{
    // Load config files.
    
    // Run command loop.
    ht_init();
    sigaction(SIGINT, &(struct sigaction){ .sa_handler = sighandler }, NULL);
    shell_loop();
    // Cleanup.
    
    return EXIT_SUCCESS;
}
