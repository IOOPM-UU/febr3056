#pragma once

#include "hash_table_iterator.h"
#include <stdlib.h>
#include <stddef.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>


/**
* @file hash_table.h
* @author write both your names here
* @date write the date you started working on this
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/



typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result where we store the value of the key, if it exists.
/// @return true if such a key exists, false otherwise. 
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
int ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, char *key);

/// @brief check if a key exists in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return true if such a key exists, false otherwise. 
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key);

/// @brief check if table is empty
/// @param ht hash table to check
/// @return true if table has entries (except sentinel nodes), otherwise false. 
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief get size of a tible
/// @param ht hash table to check
/// @return total number of entries (except sentinel nodes) in table. 
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);