#include "hash_table.h"
#include "hash_table_iterator.h"
#include "ticket4/common.h"


size_t ioopm_hash_fn(elem_t key) {
	//STUB
	(elem_t) key;
	return 0;
}
	


bool ioopm_key_eq_fn(elem_t a, elem_t b) {
	//STUB
	(elem_t) a;
	(elem_t) b;

	
	return false;
}

bool ioopm_key_eq_fn_str(elem_t a, elem_t b) {
	return strcmp(a.s, b.s) == 0;
}

bool ioopm_key_eq_fn_int(elem_t a, elem_t b) {
	return a.i == b.i;
}



/////////////////////////////////////// HASH TABLE FUNCTIONS ////////////////////////////////////////////////////////////////
static size_t string_knr_hash(const char *str)
{
	size_t result = 0;
	while (*str != '\0')
	{
		result = result * 31 + ((unsigned char)*str);
		str++;
	}
	return result;
}
size_t ioopm_hash_fn_str(elem_t key) {
	return string_knr_hash(key.s);
}
size_t ioopm_hash_fn_int(elem_t key) {
	return key.i;
}


ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
	ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
	ht->hash_fn = hash_fn;
	ht->key_eq_fn = key_eq_fn;
	return ht;
}

static void ioopm_hash_table_destroy_HELPER(entry_t **entry)
{								   // uses double pointers to evade vanishing argument variables when function gets popped from stack.
	entry_t *tmp = (*entry)->next; // If current node's next pointer points somewhere, place that next node in a temporary variable.
	Free(*entry);				   // Delete the current node and ...
	*entry = tmp;				   // ... see the next node as the current node.
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{ //
	if (ht != NULL)
	{
		for (size_t i = 0; i < No_buckets; ++i)
		{ //
			if (ht->buckets[i].next != NULL)
			{											// If a bucket contains something ...
				entry_t *current = ht->buckets[i].next; // ... name the first node, in that bucket, 'current'.
				while (current != NULL)
				{ // While the current node is NOT null ...
					if (current->next != NULL)
					{ // ... check whether its next pointer points somewhere.
						ioopm_hash_table_destroy_HELPER(&current);
					}
					else
					{
						Free(current);
					}
				}
			}
		}
		Free(ht);
	}
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key)
{
	// find bucket
	//size_t bucket = string_knr_hash(key) % No_buckets;

	size_t bucket = ht->hash_fn(key) % No_Buckets;

	// look for an entry with the key we want
	entry_t *previous /*aka sentinel in the beginning*/ = &ht->buckets[bucket]; //{ .key = NULL, .value = 0, .next = ht->buckets[bucket].next};
	while (previous->next != NULL /*&& !ht->key_eq_fn(previous->next->key, key)*/)
	{
		if (ht->key_eq_fn(previous->next->key, key)) {
			break;
		}
		previous = previous->next;
	}
	return previous;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
	entry_t *result;
	result = calloc(1, 2 * sizeof(entry_t)); //
	result->key = key;
	result->value = value;
	result->next = next;
	return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
	// find previous entry, or the last entry if the key does not exist
	entry_t *previous = find_previous_entry(ht, key);

	// if the key exists, update the value, otherwise create a new entry
	if (previous->next != NULL)
	{
		previous->next->value = value;
	}
	else
	{
		previous->next = entry_create(key, value, NULL);
	}
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{

	entry_t *previous = find_previous_entry(ht, key);
	// if the key exists, return the value, otherwise, indicate that the lookup failed
	if (previous->next != NULL)
	{
		*result = previous->next->value;
		return true;
	}
	else
	{
		return false;
	}
}

elem_t ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, elem_t key)
{
	elem_t result = int_elem(0);
	entry_t *previous = find_previous_entry(ht, key);
	if (ioopm_hash_table_lookup(ht, key, &result))
	{
		entry_t *tmp = previous->next->next; // If current node's next pointer points somewhere, place that next node in a temporary variable.
		result = previous->next->value;
		Free(previous->next); // Delete the current node and ...
		previous->next = tmp; // ... see the next node as the current node.
	}

	return result;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
	elem_t result = int_elem(0);
	return ioopm_hash_table_lookup(ht, key, &result);
}

static size_t bucket_size(entry_t *entry)
{

	size_t entries = 0;

	while (entry != NULL)
	{
		entry = entry->next;
		entries += 1;
	}
	return entries;
}
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
	size_t size = 0;
	for (size_t i = 0; i < No_buckets; i++)
	{
		size += bucket_size(ht->buckets[i].next);
	}
	return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
	//
	return (ioopm_hash_table_size(ht) == 0);
}