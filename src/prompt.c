#include <stdlib.h>
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
		    cwd = getcwd(cwd, PROMPT_BUFFER);
		    if (!cwd) {
			continue;
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
