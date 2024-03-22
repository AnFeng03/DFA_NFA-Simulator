#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dfa.h"

struct dfa {
    int current_state;
    int num_states;
    bool* accept_table;
    int** transition_table;
};

DFA newDFA(int num_states) {
    // Allocate DFA
    DFA dfa = (DFA)malloc(sizeof(struct dfa));

    // Initialize DFA
    dfa->current_state = 0;
    dfa->num_states = num_states;

    // Allocate transition table
    dfa->transition_table = (int**)malloc(num_states * sizeof(int*));

    // Initialize transition table
    for (int i = 0; i < num_states; i++) {
        dfa->transition_table[i] = (int *)malloc(128 * sizeof(int));
        for (int j = 0; j < 128; j++) {
            dfa->transition_table[i][j] = 0;
        }
    }

    // Allocate acceptance table
    dfa->accept_table = (bool*)malloc(num_states * sizeof(bool));

    // Initialize acceptance table
    for (int i = 0; i < num_states; i++) {
        dfa->accept_table[i] = false;
    }

    return dfa;
}

void freeDFA(DFA dfa) {
    for (int i = 0; i < dfa->num_states; i++) {
        free(dfa->transition_table[i]);
    }
    free(dfa->transition_table);
    free(dfa->accept_table);
    free(dfa);
}

int DFAsize(DFA dfa) {
    return dfa->num_states;
}

int DFA_get_transition(DFA dfa, int src, char sym) {
    int n = sym;
    return dfa->transition_table[src][n];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
    int n = sym;
    dfa->transition_table[src][n] = dst;
}

void DFA_set_transition_all(DFA dfa, int src, int dst) {
    for (int j = 0; j < 128; j++) {
        dfa->transition_table[src][j] = dst;
    }
}

void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa->accept_table[state] = value;
}

bool DFA_get_accepting(DFA dfa, int state) {
    return dfa->accept_table[state];
}

bool DFA_execute(DFA dfa, char *input) {
    dfa->current_state = 0;
    for (int i = 0; i < strlen(input); i++) {
        int cur = dfa->current_state;
        int sym = input[i];
        dfa->current_state = DFA_get_transition(dfa, cur, sym);
    }
    return DFA_get_accepting(dfa, dfa->current_state);
}

int DFA_size(DFA dfa) {
    return dfa->num_states;
}

void DFA_printStates(DFA dfa) {
    printf("Number of States: %d\n", DFA_size(dfa));
}
