#include "linked_list.h"

#include <stdlib.h>
#include <stddef.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>



struct list
{   
    int size;
    node_t *first;
    node_t *last;
};
struct node
{
    int value;
    node_t *next;
};



ioopm_list_t *ioopm_list_create(void) {
    ioopm_list_t *li = calloc(1, sizeof(ioopm_list_t));
    return li;
}

void ioopm_list_destroy(ioopm_list_t *list) {
    if (ioopm_list_size(list) == 0) {
    }
    else if (ioopm_list_size(list) == 1) {
        Free(list->first);
        list->last = NULL;
    }
    else {
        Free(list->first);
        Free(list->last);
    }
    Free(list);
    
}

void ioopm_list_append(ioopm_list_t *list, int value) {
    node_t *pNode = calloc(1, sizeof(node_t));
    pNode->value = value;
    pNode->next = NULL;
    if (ioopm_list_is_empty(list)) { // empty list case
        list->first =  pNode;
        list->last = pNode;
    }
    else if (ioopm_list_size(list) == 1) { // singelton list case
        list->first->next = pNode;
        list->last = pNode;
    } 
    else { // multiton list case
        node_t *old_last_node = list->last;
        list->last = pNode;
        old_last_node->next = pNode;
        
    }
    list->size += 1;
}
void ioopm_list_prepend(ioopm_list_t *list, int value) {
    node_t *pNode = calloc(1, sizeof(node_t));
    pNode->value = value;
    pNode->next = NULL;
    if (ioopm_list_is_empty(list)) { // empty list case
        list->first =  pNode;
        list->last = pNode;
        //list->last =  pNode;   	   //oldcode
        //pNode->next = list->first;   //oldcode
    }
    else if (ioopm_list_size(list) == 1) { // singelton list case
        pNode->next = list->first;
        list->first = pNode;
    } 
    else {                                 // multiton list case 
        pNode->next = list->first;
        list->first = pNode;
    }  
    list->size += 1;
}
int ioopm_list_head(ioopm_list_t *list) {
    return list->first->value;
}

int ioopm_list_last(ioopm_list_t *list) {
    return list->last->value;
}
int ioopm_list_size(ioopm_list_t *list) {
    return list->size;
}


void ioopm_list_insert(ioopm_list_t *list, int index, int value) {
    assert(0 <= index && index <= ioopm_list_size(list)); // this is the precond
    
    node_t *node_to_insert = calloc(1, sizeof(node_t));
    node_to_insert->value = value;
    if (index == 0)  { // same as prepend
        ioopm_list_prepend(list, value);
    }
    else if (index == ioopm_list_size(list)) { // same as append
        ioopm_list_append(list, value);
    }
    else {
        node_t *current_node = list->first;
        for (int i = 0; i < index; ++i) { // traverse list to index
            current_node = current_node->next;
        }
        node_t *temp = current_node->next->next;
        current_node->next = node_to_insert;
        node_to_insert->next = temp;
        list->size += 1;
    }
}   

int ioopm_list_remove(ioopm_list_t *list, int index) {
    assert(0 <= index);                           // This checks the precondtion.   
    assert(index <= (ioopm_list_size(list) - 1)); // This checks the precondtion.
    if (ioopm_list_is_empty(list)) { // anrop av  list_remove på tom lista ger error
        printf("\n\n ERROR: list_remove was fed an empty list. Exiting with -67\n\n");
        exit(-67);
    }
    //a lot of abstraction possible here.
    else if (ioopm_list_size(list) == 1) { // anrop av  list_remove på singelton-lista 
        assert(index == 0);
        int removed_value = list->first->value;
        Free(list->first);
        list->last = NULL;
        list->size -= 1;
        assert(list->size == 0);
        return removed_value;
    }
    else if (index == 0) { // anrop av list_remove på FÖRSTA elementet i multiton lista 
        node_t *to_remove = list->first;
        int removed_value = to_remove->value;
        list->first = list->first->next; //rewire list->first
        Free(to_remove);
        list->size -= 1;
        return removed_value;
    }
    else if (index == (ioopm_list_size(list) - 1)) {    // anrop av list_remove på SISTA elementet i multiton lista 
        node_t *to_remove = list->last;
        int removed_value = to_remove->value;
        node_t *node_b4_remove_target = list->first;//Start on first node and....
        for (int i = 0; i < (index - 1); ++i) { // ....traverse list to node_b4_remove_target.
            node_b4_remove_target = node_b4_remove_target->next;
        }
        list->last = node_b4_remove_target; //rewire list->last
        Free(to_remove);
        list->size -= 1;
        return removed_value;
    }
    else { // anrop av list_remove på MITTEN-ELEMENT i multiton lista.
        node_t *node_b4_target_node = list->first;
        for (int i = 0; i < (index - 1); ++i) { // traverse list to index-1
            node_b4_target_node = node_b4_target_node->next;
        }
        node_t *to_remove = node_b4_target_node->next;
        int removed_value = to_remove->value;
        node_b4_target_node->next = to_remove->next;
        Free(to_remove);
        list->size -= 1;
        return removed_value;
    }
}

int ioopm_list_get(ioopm_list_t *list, int index) {
    //copied from remove
    //remove all parts that actually removes the entry.
    //change parts that assume size has been decreased (asserts/assignments)
    //change name of all variable (eg those named to_remove)
    assert(0 <= index);                           // This checks the precondtion.   
    assert(index <= (ioopm_list_size(list) - 1)); // This checks the precondtion.
    if (ioopm_list_is_empty(list)) { // anrop av  list_get på tom lista ger error
        printf("\n\n ERROR: list_get was fed an empty list. Exiting with -67\n\n");
        exit(-67);
    } else if (index == 0) { // anrop av list_get på FÖRSTA elementet i multiton lista 
        return list->first->value;
    }
    else if (index == (ioopm_list_size(list) - 1)) {    // anrop av list_get på SISTA elementet i multiton lista 
        return list->last->value;
    }
    else { // anrop av list_get på MITTEN-ELEMENT i multiton lista.
        node_t *current_node = list->first;
        for (int i = 0; i < index; ++i) { // traverse list to index
            current_node = current_node->next;
        }
        return current_node->value;
    }
}


bool ioopm_list_is_empty(ioopm_list_t *list) {
    return list->size == 0;
}

////////////////////////////////////////////////////////////////////////