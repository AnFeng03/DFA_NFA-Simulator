#ifndef _LinkedList_h_gf
#define _LinkedList_h_gf

#include <stdbool.h>

typedef struct LinkedList LinkedList;
extern LinkedList *LinkedList_new(void);
extern void LinkedList_free(LinkedList *list, bool free_data_also);
extern void LinkedList_add_at_front(LinkedList *list, void *value);
extern void LinkedList_add_at_end(LinkedList *list, void *value);
extern bool LinkedList_contains(const LinkedList *list, void *value);
extern void LinkedList_remove(LinkedList *list, void *data);
extern void *LinkedList_element_at(LinkedList *list, int index);
extern int LinkedList_size(const LinkedList *list);
typedef struct LinkedListNode *LinkedListIterator;
extern LinkedListIterator *LinkedList_iterator(const LinkedList *list);
extern bool LinkedListIterator_has_next(const LinkedListIterator *iterator);
extern void *LinkedListIterator_next(LinkedListIterator *iterator);

#endif
