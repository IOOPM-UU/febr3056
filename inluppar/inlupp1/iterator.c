#include "hash_table_iterator.h"
#include "iterator.h"


//bad name for a file
struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  size_t current_bucket;
  entry_t *current_entry;
};


static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
  // advance to the next entry in the bucket
  it->current_entry = it->current_entry->next;

  // if it was null advance to the next bucket
  if (it->current_entry == NULL)
  {
    it->current_bucket += 1;

    // if the next bucket existed, update the current entry
    if (it->current_bucket != No_buckets)
    {
      it->current_entry = &it->ht->buckets[it->current_bucket];
    }
  }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it)
{
    //&it->ht->buckets[it->current_bucket] is the sentinel node
  while (it->current_bucket < No_buckets &&
         it->current_entry == &it->ht->buckets[it->current_bucket])
  {
    advance_iterator_state(it); // Cheat!
  }
}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht) {
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = &(ht->buckets[0]);

    skip_sentinel_nodes(it);

    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it) {
    Free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it) {
  // *should* only need to check if equal, but this is safer for now
  return it->current_bucket >= No_Buckets /*- 1*/;
}

/*
static int bucket_size(entry_t *entry) {
  
int entries = 0;

while (entry != NULL) {
  entry = entry->next;
  entries += 1;
}
return entries;
}
*/
void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it) {
    advance_iterator_state(it);
    skip_sentinel_nodes(it);
}
elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it) {
    return it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it) {
    return it->current_entry->value;
}