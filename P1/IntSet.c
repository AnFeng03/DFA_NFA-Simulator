#include <stdlib.h>
#include <stdio.h>
#include "IntSet.h"

struct IntSet {
    int* elements;
    int size;
};

IntSet IntSet_new(void) {
    IntSet new_set = (IntSet)malloc(sizeof(struct IntSet));
    new_set->size = 0;
    new_set->elements = NULL;
    return new_set;
}

void IntSet_free(IntSet set) {
    if (set != NULL) {
        free(set->elements);
        free(set);
    }
}

bool IntSet_is_empty(const IntSet set) {
    return set->size == 0;
}

void IntSet_add(IntSet set, int value) {
    if (value < 0) {
        fprintf(stderr, "IntSet_add: value out of range: %d\n", value);
        abort();
    }

    // Check if the value already exists in the set
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return; // Value already in the set
        }
    }

    // Allocate memory for the new element
    set->size++;
    set->elements = (int*)realloc(set->elements, set->size * sizeof(int));

    // Add the new value to the set
    set->elements[set->size - 1] = value;
}

bool IntSet_contains(const IntSet set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return true;
        }
    }
    return false;
}

void IntSet_union(IntSet set1, const IntSet set2) {
    for (int i = 0; i < set2->size; i++) {
        IntSet_add(set1, set2->elements[i]);
    }
}

bool IntSet_contains_all(IntSet set1, IntSet set2) {
    for (int i = 0; i < set2->size; i++) {
        if (!IntSet_contains(set1, set2->elements[i])) {
            return false;
        }
    }
    return true;
}

bool IntSet_equals(IntSet set1, IntSet set2) {
    if (set1->size != set2->size) {
        return false;
    }

    for (int i = 0; i < set1->size; i++) {
        if (!IntSet_contains(set2, set1->elements[i])) {
            return false;
        }
    }
    return true;
}

struct IntSetIterator {
    IntSet set;
    int index;
};

IntSetIterator IntSet_iterator(const IntSet set) {
    IntSetIterator iterator = (IntSetIterator)malloc(sizeof(struct IntSetIterator));
    iterator->set = set;
    iterator->index = 0;
    return iterator;
}

bool IntSetIterator_has_next(const IntSetIterator iterator) {
    return iterator->index < iterator->set->size;
}

int IntSetIterator_next(IntSetIterator iterator) {
    if (IntSetIterator_has_next(iterator)) {
        int value = iterator->set->elements[iterator->index];
        iterator->index++;
        return value;
    } else {
        return -1;
    }
}
