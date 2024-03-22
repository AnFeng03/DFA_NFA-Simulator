#include <stdio.h>
#include <stdlib.h>
#include "IntSet.h"
#include "LinkedList.h"


struct LinkedList {
    struct LinkedListNode *first;
    struct LinkedListNode *last;
    int size;
};

typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;


LinkedList * LinkedList_new(void) {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->first = list->last = NULL;
    list->size=0;
    return list;
}

int LinkedList_size(const LinkedList *list){
    return list->size;
}

static LinkedListNode * LinkedListNode_new(void *data) {
    LinkedListNode *node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        abort();
    }
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}


void LinkedList_free(LinkedList *list, bool free_data_also) {
    // Free the elements
    LinkedListNode *elt = list->first;
    while (elt != NULL) {
        LinkedListNode *next = elt->next;
        if (free_data_also && elt->data != NULL) {
            free(elt->data);
        }
        free(elt);
        elt = next;
    }
    // Free the list itself
    free(list);
}

void LinkedList_add_at_front(LinkedList *list, void *data) {
    list->size +=1;
    LinkedListNode *node = LinkedListNode_new(data);
    node->next = list->first;
    if (list->first != NULL) {
        list->first->prev = node;
    }
    list->first = node;
    if (list->last == NULL) {
        list->last = node;
    }
}

void LinkedList_add_at_end(LinkedList *list, void *data) {
    list->size +=1;
    LinkedListNode *node = LinkedListNode_new(data);
    node->prev = list->last;
    if (list->last != NULL) {
        list->last->next = node;
    }
    list->last = node;
    if (list->first == NULL) {
        list->first = node;
    }
}

bool LinkedList_contains(const LinkedList *list, void *data) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
        // if (node->data == data) {
        if (IntSet_equals(node->data, data)) {
            return true;
        }
    }
    return false;
}

void LinkedList_remove(LinkedList *list, void *data) {
    list->size -=1;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
        if (node->data == data) {
            if (node == list->first) {
                list->first = node->next;
            }
            if (node == list->last) {
                list->last = node->prev;
            }
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            free(node);
            return;
        }
    }
}

void * LinkedList_element_at(LinkedList *list, int index) {
    int i = 0;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
        if (i == index) {
            return node->data;
        }
        i += 1;
    }
    return NULL;
}

LinkedListIterator * LinkedList_iterator(const LinkedList *list) {
    LinkedListIterator *iterator = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
    *iterator = list->first;
    return iterator;
}

bool LinkedListIterator_has_next(const LinkedListIterator *iterator) {
    return iterator != NULL && *iterator != NULL;
}

void * LinkedListIterator_next(LinkedListIterator *iterator) {
    if (iterator == NULL || *iterator == NULL) {
        return NULL;
    } else {
        void *data = (*iterator)->data;
        *iterator = (*iterator)->next;
        return data;
    }
}

