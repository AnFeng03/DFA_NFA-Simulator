#ifndef _IntSet_h
#define _IntSet_h

#include <stdbool.h>

typedef struct IntSet* IntSet;
extern IntSet IntSet_new(void);
extern void IntSet_free(IntSet set);
extern bool IntSet_is_empty(const IntSet set);
extern void IntSet_add(IntSet set, int value);
extern bool IntSet_contains(const IntSet set, int value);
extern void IntSet_union(IntSet set1, const IntSet set2);
extern bool IntSet_equals(IntSet set1, IntSet set2);
typedef struct IntSetIterator *IntSetIterator;
extern IntSetIterator IntSet_iterator(const IntSet set);
extern bool IntSetIterator_has_next(const IntSetIterator iterator);
extern int IntSetIterator_next(IntSetIterator iterator);

#endif
