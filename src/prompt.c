/* prompt.c -- the prompt functions

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
#include <regex.h>
#include "prompt.h"
#include "config.h"
#include "datetime.h"

#define PROMPT_BUFFER 256

typedef struct prompt_s {
    unsigned int len;
    size_t size;
    char *str;
} prompt_t;

char *
strfcat(char *restrict dest, size_t n, char *restrict src)
{
    int i = n;
    int j = 0;
    while(src[i] != '\0') {
	dest[j++] = src[i++];
    }
    dest[j] = '\0';
    return dest;
}

char *
strintr(char *restrict dest, size_t n, char *restrict substr)
{
    char *tmp = (char *) malloc(strlen(dest) + 1);
    strfcat(tmp, n, dest);
    dest[n - 2] = '\0';
    strcat(dest, substr);
    strcat(dest, tmp);
    return dest;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;

    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

char *
prompt()
{
    char *cwd = (char *) malloc(sizeof(char) * PROMPT_BUFFER);
    char *login;
    char *host = (char *) malloc(sizeof(char) * 64);
    prompt_t *shell_prompt = (prompt_t *) malloc(sizeof(prompt_t));
    shell_prompt->len = 0;
    shell_prompt->size = sizeof(char) * PROMPT_BUFFER;
    shell_prompt->str = (char *) malloc(shell_prompt->size);
    strcpy(shell_prompt->str, PROMPT);
    for (int i = 0; i < strlen(shell_prompt->str); i++) {
	if (shell_prompt->str[i] == '%') {
	    switch(shell_prompt->str[i + 1]) {
		case '?':
		    break;
		case 'd':
		    cwd = getcwd(cwd, PROMPT_BUFFER);
		    if (!cwd) {
			break;
		    } 
		    strintr(shell_prompt->str, i + 2, cwd);
		    i += strlen(cwd) - 1;
		    break;
		case '~':
		    regex_t regex;
		    cwd = getcwd(cwd, PROMPT_BUFFER);
		    char *home = getenv("HOME");
		    if (!cwd) {
			continue;
		    } 
		    if (regcomp(&regex, home, 0) == 0) {
			if (regexec(&regex, cwd, 0, NULL, 0) == 0) {
			    cwd = str_replace(cwd, home, "~");
			}
		    }
		    strintr(shell_prompt->str, i + 2, cwd);
		    i += strlen(cwd) - 1;
		    break;
		case 'l':
		    login = getlogin();
		    if (!login ) {
			continue;
		    }
		    strintr(shell_prompt->str, i + 2, login);
		    i += strlen(login) - 1;
		    break;
		case 'h':
		    gethostname(host, 64);
		    strintr(shell_prompt->str, i + 2, host);
		    i += strlen(host) - 1;
		    break;
		case 'D':
		    char *date = dt_date();
		    strintr(shell_prompt->str, i + 2, date);
		    i += strlen(date) - 1;
		    free(date);
		    break;
		case 'm':
		    char *month = dt_month();
		    strintr(shell_prompt->str, i + 2, month);
		    i += strlen(month) - 1;
		    free(month);
		    break;
		case 'y':
		    char *year = dt_year();
		    strintr(shell_prompt->str, i + 2, year);
		    i += strlen(year) - 1;
		    free(year);
		    break;
		case 'a':
		    char *day = dt_day();
		    strintr(shell_prompt->str, i + 2, day);
		    i += strlen(day) - 1;
		    free(day);
		    break;
		case 'T':
		    char *time24 = dt_time24();
		    strintr(shell_prompt->str, i + 2, time24);
		    i += strlen(time24) - 1;
		    free(time24);
		    break;
		case 't':
		    char *time12 = dt_time12();
		    strintr(shell_prompt->str, i + 2, time12);
		    i += strlen(time12) - 1;
		    free(time12);
		    break;
	    }
	}
    }
    free(cwd);
    free(host);

    return shell_prompt->str;
}
