#include <stdbool.h>
#include <stdlib.h>
#include "nfa_to_dfa.h"
#include "LinkedList.h"
#include "dfa.h"
#include "nfa.h"
#include "IntSet.h"

LinkedList* computeDFAStates(NFA nfa) {
    LinkedList* stateLabelsList = LinkedList_new();
    IntSet initialStateSet = IntSet_new();
    IntSet_add(initialStateSet, 0);
    LinkedList_add_at_front(stateLabelsList, initialStateSet);

    int currentIndex = -1;
    int listSize = 1;

    do {
        listSize = LinkedList_size(stateLabelsList);
        currentIndex++;
        IntSet currentIntSet = LinkedList_element_at(stateLabelsList, currentIndex);

        for (int charId = 0; charId < 128; charId++) {
            IntSetIterator iterator = IntSet_iterator(currentIntSet);
            IntSet nextIntSet = IntSet_new();

            while (IntSetIterator_has_next(iterator)) {
                IntSet_union(nextIntSet, NFA_get_transitions(nfa, IntSetIterator_next(iterator), charId));
            }
            free(iterator);

            if ((!LinkedList_contains(stateLabelsList, nextIntSet)) &&
                (!IntSet_is_empty(nextIntSet))) {
                LinkedList_add_at_end(stateLabelsList, nextIntSet);
            }
        }
    } while ((LinkedList_size(stateLabelsList) != listSize) ||
             (currentIndex + 1) != LinkedList_size(stateLabelsList));

    return stateLabelsList;
}

DFA createDFAFromStateList(LinkedList* stateLabelsList, NFA nfa) {
    int dfaNumStates = LinkedList_size(stateLabelsList);
    DFA dfa = newDFA(dfaNumStates);

    for (int i = 0; i < DFAsize(dfa); i++) {
        IntSet currentSet = LinkedList_element_at(stateLabelsList, i);
        for (int j = 0; j < 128; j++) {
            IntSetIterator setIterator = IntSet_iterator(currentSet);
            IntSet nextSet = IntSet_new();

            while (IntSetIterator_has_next(setIterator)) {
                IntSet_union(nextSet, NFA_get_transitions(nfa, IntSetIterator_next(setIterator), j));
            }
            free(setIterator);

            int nextStateIndex = 0;
            while (!IntSet_equals(nextSet, LinkedList_element_at(stateLabelsList, nextStateIndex))) {
                nextStateIndex++;
            }

            DFA_set_transition(dfa, i, j, nextStateIndex);
            IntSet_free(nextSet);
        }
    }

    return dfa;
}

void setAcceptingStates(DFA dfa, LinkedList* stateLabelsList, NFA nfa) {
    int dfaStateIndex = 0;
    LinkedListIterator* acceptIterator = LinkedList_iterator(stateLabelsList);

    while (LinkedListIterator_has_next(acceptIterator)) {
        IntSet currentSet = LinkedListIterator_next(acceptIterator);
        IntSetIterator setIterator = IntSet_iterator(currentSet);

        while (IntSetIterator_has_next(setIterator)) {
            int currentState = IntSetIterator_next(setIterator);

            if (NFA_get_accepting(nfa, currentState)) {
                DFA_set_accepting(dfa, dfaStateIndex, true);
            }
        }
        free(setIterator);
        dfaStateIndex++;
    }

    free(acceptIterator);
}


DFA nfa_to_dfa(NFA nfa) {
    LinkedList* stateLabelsList = computeDFAStates(nfa);
    DFA dfa = createDFAFromStateList(stateLabelsList, nfa);
    setAcceptingStates(dfa, stateLabelsList, nfa);
    LinkedList_free(stateLabelsList, true);

    return dfa;
}

