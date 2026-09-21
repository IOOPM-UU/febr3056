#include "hash_table.h"

#define Free(ptr) { free(ptr); ptr = NULL; }


typedef struct entry entry_t;

struct entry {
  char *key;     // holds the key
  int value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  // DODGE: hard-coding number of buckets as 17.
  // NOTE: addressing this dodge is optional.
  entry_t buckets[17];
};
/*
void Free(entry_t *ptr) {
  ptr = NULL;
}
*/
static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0') {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}
static entry_t *entry_create(char *key, int value, entry_t *next) {
  entry_t *result = calloc(1, sizeof(entry_t));
  result->key = key;
  result->value = value;
  result->next = next;
  return result;
}

void entry_destroy(entry_t *entry) {
  entry_t *tmp = entry->next;
  Free(entry);
  entry = tmp;
}


ioopm_hash_table_t *ioopm_hash_table_create(void) {
 return calloc(1, sizeof(ioopm_hash_table_t));
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
	if (ht != NULL) {
		for(size_t i = 0; i < 17; ++i) {
			if (ht->buckets[i].next != NULL) {
				entry_t *current = ht->buckets[i].next;
				//SHOULD BE A WHILE-LOOP, NEEDS TO EMPTY ALL ENTRIES.
				while (current != NULL) {
					if (current->next != NULL) {
						entry_destroy(current);
					} else {
						Free(current);
					}
				}
			}
    	}
		Free(ht);
	}
}
entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key) {
  size_t bucket = string_knr_hash(key) % 17;



  entry_t *previous = &ht->buckets[bucket];
  
  if (previous->next == NULL) {
    return previous;
  }
  
  while (previous->next != NULL && strcmp(previous->next->key, key) != 0)
  {
    previous = previous->next;
  }
  return previous;  
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
  entry_t *previous = find_previous_entry(ht, key);
  // if the key exists, update the value, otherwise, add a new entry to the end of the list
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL);
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result) {

	// look for an entry with the key we want

  /*
	entry_t *current = ht->buckets[bucket].next;
	while (current != NULL && strcmp(current->key, key) != 0) {
		current = current->next;
	}
  */
  entry_t *previous = find_previous_entry(ht, key);

	// if the key exists, return the value, otherwise, indicate that the lookup failed
	if (previous->next != NULL) {
		*result = previous->next->value;
		return true;
	}
	else {
		return false;
	}
}
