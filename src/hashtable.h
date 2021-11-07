/* hash_table.h -- header file for hash_table.c.

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
#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#define HT_INITIAL_BASE_SIZE 10
#define HT_PRIME_1 12289
#define HT_PRIME_2 6151

typedef struct {
    char *key;
    char *helpmsg;
    int (*func) (char **);
} ht_item;

typedef struct {
    int size;
    int base_size;
    int count;
    ht_item **items;
} ht_table;

int is_prime(const int x);
int next_prime(int x);

// init and delete
ht_table *ht_new();
void ht_del_table(ht_table *ht);

// HASH TABLE API
void ht_insert(ht_table *ht, const char *key, const char *helpmsg, const int (*func)(char **args));
char *ht_get_help(ht_table *ht, const char *key);
int ht_run_func(ht_table *ht, const char *key, char **args);
int ht_search(ht_table *ht, const char *key);
void ht_delete(ht_table *ht, const char *key);

#endif
