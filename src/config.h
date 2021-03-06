/* config.h -- the main config file

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
#ifndef CONFIG_H_
#define CONFIG_H_
#define INPUTRC		"INPUTRC=/etc/inputrc"

// Prompt styling

#define RESET		"\e[0m"

#define BOLD		"\e[1m"
#define RSTBOLD		"\e[21m"

#define DIM		"\e[2m"
#define RSTDIM		"\e[22m"

#define UNDER		"\e[4m"
#define RSTUNDER	"\e[24m"

#define BLINK		"\e[5m"
#define RSTBLINK	"\e[25m"

#define REVERSE		"\e[7m"
#define RSTREVERSE	"\e[27m"

#define HIDDEN		"\e[8m"
#define RSTHIDDEN	"\e[28m"

// Forground colors
#define FCOLOR_DFLT	"\e[39m" 	// default forground color
#define FCOLOR_BLACK	"\e[30m"
#define FCOLOR_RED	"\e[31m"
#define FCOLOR_LRED	"\e[91m"
#define FCOLOR_GREEN	"\e[32m"
#define FCOLOR_LGREEN	"\e[92m"
#define FCOLOR_YELLOW	"\e[33m"
#define FCOLOR_LYELLOW	"\e[93m"
#define FCOLOR_BLUE	"\e[34m"
#define FCOLOR_LBLUE	"\e[94m"
#define FCOLOR_MAEGNTA	"\e[35m"
#define FCOLOR_LMAEGNTA	"\e[95m"
#define FCOLOR_CYAN	"\e[36m"
#define FCOLOR_LCYAN	"\e[96m"
#define FCOLOR_LGRAY	"\e[37m"
#define FCOLOR_DGRAY	"\e[90m"
#define FCOLOR_WHITE	"\e[97m"

// Background colors
#define BCOLOR_DFLT	"\e[49m" 	// default background color
#define BCOLOR_BLACK	"\e[40m"
#define BCOLOR_RED	"\e[41m"
#define BCOLOR_LRED	"\e[101m"
#define BCOLOR_GREEN	"\e[42m"
#define BCOLOR_LGREEN	"\e[102m"
#define BCOLOR_YELLOW	"\e[43m"
#define BCOLOR_LYELLOW	"\e[103m"
#define BCOLOR_BLUE	"\e[44m"
#define BCOLOR_LBLUE	"\e[104m"
#define BCOLOR_MAEGNTA	"\e[45m"
#define BCOLOR_LMAEGNTA	"\e[105m"
#define BCOLOR_CYAN	"\e[46m"
#define BCOLOR_LCYAN	"\e[106m"
#define BCOLOR_LGRAY	"\e[47m"
#define BCOLOR_DGRAY	"\e[100m"
#define BCOLOR_WHITE	"\e[107m"

// Prompt Escapes
// %d 	==>	Current working directory
// %~ 	==>	%d but replace $HOME with '~'
// %l	==>	Login name
// %h	==>	Host name
// %?	==>	Return status of the last executed command
// %D	==> 	Date in yy-mm-dd format
// %m	==>	Month
// %y 	==>	Year
// %a	==> 	Day
// %T	==> 	Current time in 24-hour format
// %t	==>	Current time in 12-hour format
const char *PROMPT = "%~ " FCOLOR_RED BOLD "> " RESET;

#endif
