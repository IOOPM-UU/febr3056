#include "list_iterator.h"


struct list_iterator
{
  ioopm_list_t *list;
  node_t *current_node;
};



/// @brief Create a new iterator
/// @param l the list to iterate over
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l) {
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));

    it->list = l;
    it->current_node = l->first;
    return it;
}

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter) {
    Free(iter);
}
/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return true if there are no more elements after current node
bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter) {
    // first case handles empty list case ------------- second case makes <<test_iterate_singleton_list>> pass
    return ((iter->list->last == iter->current_node) || (iter->list->last->next == NULL));
}
//tested:
////one application takes a singleton list to its end.
///
/// @brief Step the iterator forward one step
/// @param iter the iterator
void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter) {
    iter->current_node = iter->current_node->next; // previously just: iter->current_node->next
}
//is tested:
//one application takes a singleton list to its end.

/// @brief Return the current element from the underlying list
/// @param iter the iterator
/// @return the current element
elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter) {
    return iter->current_node->value;
}
//--------------------------< ABOVE FUNCTIONS ARE TESTED >--------------------------

/// NOTE: REMOVE IS OPTIONAL TO IMPLEMENT
/// @brief Remove the current element from the underlying list
/// @param iter the iterator
/// @return the removed element
elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter) {
    
}

/// NOTE: INSERT IS OPTIONAL TO IMPLEMENT
/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
    
}