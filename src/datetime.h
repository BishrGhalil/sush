/* datetime.h -- Header file for datetime.c

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
#ifndef _DATETIME_H_
#define _DATETIME_H_

char *dt_datetime(void);
char *dt_time24(void);
char *dt_time12(void);
char *dt_date(void);
char *dt_day(void);
char *dt_month(void);
char *dt_monthday(void);
char *dt_year(void);

#endif
