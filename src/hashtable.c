/* hash_table.c -- hash_table source file.

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
#include <string.h>
#include <math.h>

#include "hashtable.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

int is_prime(const int x) {
    if (x < 2) {
	return -1;
    }
    if (x < 4) {
	return 1;
    }
    if ((x % 2) == 0) {
	return 0;
    }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}

static ht_item *ht_new_item(const char *key, const char *helpmsg, int (*func)(char **args))
{
    ht_item *item = (ht_item *) malloc(sizeof(ht_item));
    item->key = strdup(key);
    item->helpmsg = strdup(helpmsg);
    item->func = func;
    return item;
}

static ht_table* ht_new_sized(const int base_size) {
    ht_table* ht = malloc(sizeof(ht_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

static void ht_resize(ht_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }

    ht_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->helpmsg, item->func);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_table(new_ht);
}

static void ht_resize_up(ht_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

ht_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_del_item(ht_item *i)
{
    free(i->key);
    free(i->helpmsg);
    free(i->func);
}

void ht_del_table(ht_table *ht)
{
    for (int i = 0; i < ht->size; i++){
	ht_item *item = ht->items[i];
	if (item){
	    ht_del_item(item);
	}
    }
    free(ht->items);
    free(ht);
}

static int ht_hash(const char *s, const int a, const int m)
{
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++){
	hash += (long) pow(a, len_s - (i + 1) * s[i]);
	hash = hash % m;
    }
    return (int) hash;
}

static int ht_get_hash(const char *s, const int n_buckets, const int attempt)
{
    const int hash_a = ht_hash(s, HT_PRIME_1, n_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, n_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % n_buckets;
}

// HASH TABLE API
void ht_insert(ht_table *ht, const char *key, const char *helpmsg, const int (*func)(char **args))
{
    const int load = ht->count * 100 / ht->size;
    if (load > 70){
	ht_resize_up(ht);
    }

    ht_item *item = ht_new_item(key, helpmsg, func);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item *cur_item = ht->items[index];
    int i = 1;
    while (cur_item) {
	if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
	    }
	}
	index = ht_get_hash(item->key, ht->size, i);
	cur_item = ht->items[index];
	i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char *ht_get_help(ht_table *ht, const char *key)
{
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item){
	if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->helpmsg;
	    }
	}
	index = ht_get_hash(key, ht->size, i);
	item = ht->items[index];
	i++;
    }
    return NULL;
}

int ht_run_func(ht_table *ht, const char *key, char **args)
{
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item){
	if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->func(args);
	    }
	}
	index = ht_get_hash(key, ht->size, i);
	item = ht->items[index];
	i++;
    }
    return 0;
}

int ht_search(ht_table *ht, const char *key)
{
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item) {
	if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
		return 1;
	    }
	}

	index = ht_get_hash(key, ht->size, i);
	item = ht->items[index];
	i++;
    }
    return 0;
}

// hash_table.c
void ht_delete(ht_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
	ht_resize_down(ht);
    }

    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}
