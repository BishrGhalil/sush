#include "datetime.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

char *
dt_datetime(void)
{
    time_t now = time(0);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}

char *
dt_day(void)
{
    char *time_str = dt_datetime();
    char *day = (char *) malloc(sizeof(char) * 4);
    int j = 0;
    for (int i = 0; i < 3; i++, j++) {
	day[j] = time_str[i];
    }
    day[3] = '\0';
    return day;
}

char *
dt_month(void)
{
    char *time_str = dt_datetime();
    char *month = (char *) malloc(sizeof(char) * 4);
    int j = 0;
    for (int i = 4; i < 7; i++, j++) {
	month[j] = time_str[i];
    }
    month[3] = '\0';
    return month;
}

char *
dt_monthday(void)
{
    char *time_str = dt_datetime();
    char *monthday = (char *) malloc(sizeof(char) * 2);
    monthday[0] = time_str[9];
    monthday[1] = '\0';
    return monthday;
}

char *
dt_year(void)
{
    char *time_str = dt_datetime();
    char *year = (char *) malloc(sizeof(char) * 5);
    int j = 0;
    for (int i = 20; i < 24; i++, j++) {
	year[j] = time_str[i];
    }
    year[4] = '\0';
    return year;
}

char *
dt_time24(void)
{
    char *time_str = dt_datetime();
    char *time24 = (char *) malloc(sizeof(char) * 9);
    int j = 0;
    for (int i = 11; i < 19; i++, j++) {
	time24[j] = time_str[i];
    }
    time24[9] = '\0';
    return time24;
}

char *
dt_date(void)
{
    char *date = (char *) malloc(sizeof(char) * 13);
    strcpy(date, dt_year());
    strcat(date, "-");
    strcat(date, dt_month());
    strcat(date, "-");
    strcat(date, dt_day());
    return date;
}
