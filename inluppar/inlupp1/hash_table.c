#include "hash_table.h" 

#define Free(ptr){ free(ptr); ptr = NULL; }
/////////////////////////////////////// TYPE DEFENIITONS /////////////////////////////////////////////////////////////////////
typedef struct entry entry_t;
struct entry{
	char *key;     // holds the key
	int value;     // holds the value
	entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table{
	// DODGE: hard-coding number of buckets as 17.
	// NOTE: addressing this dodge is optional.
	entry_t buckets[17];
};

/////////////////////////////////////// HASH TABLE FUNCTIONS ////////////////////////////////////////////////////////////////
static size_t string_knr_hash(const char *str) {
	size_t result = 0;
	while (*str != '\0') {
		result = result * 31 + ((unsigned char) *str);
		str++;
	}
	return result;
}

ioopm_hash_table_t *ioopm_hash_table_create(void) {
	return calloc(1, sizeof(ioopm_hash_table_t));
}

static void ioopm_hash_table_destroy_HELPER(entry_t **entry) { //uses double pointers to evade vanishing argument variables when function gets popped from stack.  
	entry_t *tmp = (*entry)->next; // If current node's next pointer points somewhere, place that next node in a temporary variable. 
	Free(*entry); // Delete the current node and ...
	entry = &tmp; // ... see the next node as the current node. 
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) { // 
	if (ht != NULL) {
		for(size_t i = 0; i < 17; ++i){ //
			if (ht->buckets[i].next != NULL){ // If a bucket contains something ...
				entry_t *current = ht->buckets[i].next; // ... name the first node, in that bucket, 'current'.
				while (current != NULL){ // While the current node is NOT null ...
					if (current->next != NULL){ // ... check whether its next pointer points somewhere.
						ioopm_hash_table_destroy_HELPER(&current);
					} 
					else{
						Free(current);
					}
				}
			}
      
    	}
		Free(ht);
	}
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key) {
	// find bucket
	size_t bucket = string_knr_hash(key) % 17;

	// look for an entry with the key we want
	entry_t *previous /*aka sentinel in the beginning*/ = &ht->buckets[bucket]; //{ .key = NULL, .value = 0, .next = ht->buckets[bucket].next};
	while (previous->next != NULL && strcmp(previous->next->key, key) != 0) {
		previous = previous->next;
	}
	return previous;
}

static entry_t *entry_create(char *key, int value, entry_t *next) {
	entry_t *result;
	result = calloc(1, 2 * sizeof(entry_t)); //
	result->key = key;
	result->value = value;
	result->next = next;
	return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value) {
  	// find previous entry, or the last entry if the key does not exist
  	entry_t *previous = find_previous_entry(ht, key);

  	// if the key exists, update the value, otherwise create a new entry
  	if (previous->next != NULL) {
		previous->next->value = value;
  	}
  	else {
  	  	previous->next = entry_create(key, value, NULL);
  	}
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result) {
	
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

int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key) {
	int result = 0;
	entry_t *previous = find_previous_entry(ht, key);
	if (ioopm_hash_table_lookup(ht, key, &result)) {
		entry_t *tmp = previous->next->next; // If current node's next pointer points somewhere, place that next node in a temporary variable. 
		result = previous->next->value;
    Free(previous->next); // Delete the current node and ...
		previous->next = tmp; // ... see the next node as the current node. 
		
	}
	
  return result;
	
}