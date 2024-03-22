#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "IntSet.h"
#include "nfa.h"

struct nfa {
    IntSet current_states;
    int num_states;
    bool* accept_table;
    IntSet** transition_table;
};

NFA newNFA(int numstates) {
    NFA nfa = (NFA)malloc(sizeof(struct nfa));

    nfa->current_states = NULL;
    nfa->num_states = numstates;

    nfa->transition_table = (IntSet**)malloc(numstates * sizeof(IntSet*));
    for (int i = 0; i < numstates; i++) {
        nfa->transition_table[i] = (IntSet*)malloc(128 * sizeof(IntSet));
    }

    for (int i = 0; i < numstates; i++) {
        for (int j = 0; j < 128; j++) {
            nfa->transition_table[i][j] = IntSet_new();
        }
    }

    nfa->accept_table = (bool*)malloc(numstates * sizeof(bool));

    for (int i = 0; i < numstates; i++) {
        nfa->accept_table[i] = false;
    }

    return nfa;
}

void freeNFA(NFA nfa) {
    for (int i = 0; i < nfa->num_states; i++) {
        for (int j = 0; j < 128; j++) {
            IntSet_free(nfa->transition_table[i][j]);
        }
        free(nfa->transition_table[i]);
    }
    free(nfa->transition_table);
    IntSet_free(nfa->current_states);
    free(nfa->accept_table);
    free(nfa);
}

void resetNFA(NFA nfa) {
    if (nfa->current_states != NULL) {
        IntSet_free(nfa->current_states);
    }
    nfa->current_states = IntSet_new();
    IntSet_add(nfa->current_states, 0);
}

IntSet NFA_get_transitions(NFA nfa, int src, char sym) {
    int n = sym;
    return nfa->transition_table[src][n];
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst) {
    int n = sym;
    if (!IntSet_contains(nfa->transition_table[src][n], dst)) {
        IntSet_add(nfa->transition_table[src][n], dst);
    }
}

void NFA_add_transition_all(NFA nfa, int src, int dst) {
    for (int j = 0; j < 128; j++) {
        if (!IntSet_contains(nfa->transition_table[src][j], dst)) {
            IntSet_add(nfa->transition_table[src][j], dst);
        }
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value) {
    nfa->accept_table[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state) {
    return nfa->accept_table[state];
}

bool NFA_execute(NFA nfa, char* input) {
    resetNFA(nfa);
    IntSet temp;
    for (int i = 0; i < strlen(input); i++) {
        int sym = input[i];

        temp = IntSet_new();
        IntSetIterator curr_iterator = IntSet_iterator(nfa->current_states);

        while (IntSetIterator_has_next(curr_iterator)) {
            int cur = IntSetIterator_next(curr_iterator);
            IntSet_union(temp, NFA_get_transitions(nfa, cur, sym));
        }
        free(curr_iterator);
        IntSet_free(nfa->current_states);
        nfa->current_states = temp;
        IntSet_union(nfa->current_states, temp);
    }
    bool accepted = false;
    IntSetIterator accept_iterator = IntSet_iterator(nfa->current_states);
    while (IntSetIterator_has_next(accept_iterator)) {
        int cur = IntSetIterator_next(accept_iterator);
        if (nfa->accept_table[cur] == true) {
            accepted = true;
        }
    }

    free(accept_iterator);
    return accepted;
}
