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
		case 'd':
		    cwd = getcwd(cwd, PROMPT_BUFFER);
		    if (!cwd) {
			continue;
		    } 
		    strintr(shell_prompt->str, i + 2, cwd);
		    break;
		case 'l':
		    login = getlogin();
		    if (!login ) {
			continue;
		    }
		    strintr(shell_prompt->str, i + 2, login);
		    break;
		case 'h':
		    gethostname(host, 64);
		    strintr(shell_prompt->str, i + 2, host);
		    break;
		case 'D':
		    char *date = dt_date();
		    strintr(shell_prompt->str, i + 2, date);
		    free(date);
		    break;
		case 'm':
		    char *month = dt_month();
		    strintr(shell_prompt->str, i + 2, month);
		    free(month);
		    break;
		case 'y':
		    char *year = dt_year();
		    strintr(shell_prompt->str, i + 2, year);
		    free(year);
		    break;
		case 'a':
		    char *day = dt_day();
		    strintr(shell_prompt->str, i + 2, day);
		    free(day);
		    break;
		case 'T':
		    char *time = dt_time24();
		    strintr(shell_prompt->str, i + 2, time);
		    free(time);
		    break;
	    }
	}
    }
    free(cwd);
    free(host);

    return shell_prompt->str;
}