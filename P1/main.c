#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "nfa_to_dfa.h"

DFA DFA_for_CSC(void) {
    DFA dfa = newDFA(4); // There are 4 states in the DFA
    DFA_set_accepting(dfa, 3, true); // State 3 is accepting
    DFA_set_transition(dfa, 0, 'C', 1);
    DFA_set_transition(dfa, 1, 'S', 2);
    DFA_set_transition(dfa, 2, 'C', 3);
    return dfa;
}

DFA DFA_for_contains_end(void) {
    DFA dfa = newDFA(4);
    DFA_set_accepting(dfa, 3, true);

    DFA_set_transition(dfa, 0, 'e', 1);
    for (char c = 0; c < 127; c++) {
        if (c != 'e') {
            DFA_set_transition(dfa, 0, c, 0);
        }
    }

    DFA_set_transition(dfa, 1, 'e', 1);
    DFA_set_transition(dfa, 1, 'n', 2);
    for (char c = 0; c < 127; c++) {
        if (c != 'n' && c != 'e') {
            DFA_set_transition(dfa, 1, c, 0);
        }
    }

    DFA_set_transition(dfa, 2, 'd', 3);
    for (char c = 0; c < 127; c++) {
        if (c != 'd') {
            DFA_set_transition(dfa, 2, c, 0);
        }
    }

    for (char c = 0; c < 127; c++) {
            DFA_set_transition(dfa, 3, c, 3);
    }

    return dfa;
}

DFA DFA_for_starts_with_vowel(void) {
    DFA dfa = newDFA(2); // There are 5 states in the DFA
    DFA_set_accepting(dfa, 1, true); // State 0 is accepting
    DFA_set_transition(dfa, 0, 'a', 1);
    DFA_set_transition(dfa, 0, 'e', 1);
    DFA_set_transition(dfa, 0, 'i', 1);
    DFA_set_transition(dfa, 0, 'o', 1);
    DFA_set_transition(dfa, 0, 'u', 1);
    DFA_set_transition_all(dfa, 1, 1);
    return dfa;
}

DFA DFA_for_even_binary(void) {
    DFA dfa = newDFA(2); // There are 2 states in the DFA
    DFA_set_accepting(dfa, 0, true); // State 0 is accepting
    DFA_set_transition(dfa, 0, '0', 1);
    DFA_set_transition(dfa, 0, '1', 1);
    DFA_set_transition(dfa, 1, '0', 0);
    DFA_set_transition(dfa, 1, '1', 0);
    return dfa;
}

bool runDFA(DFA dfa, char* input) {
    bool result = DFA_execute(dfa, input);
    printf("Result for input \"%s\": %s\n", input, result ? "true" : "false");
    return result;
}

void DFA_repl(DFA dfa) {
    char input[256];
    printf("Enter an input (\"quit\" to quit): ");
    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline
        if (strcmp(input, "quit") == 0) {
            break;
        }
        runDFA(dfa, input);
        printf("Enter an input (\"quit\" to quit): ");
    }
}

bool NFA_run(NFA nfa, char* input) {
    return NFA_execute(nfa, input);
}

void NFA_repl(NFA nfa) {
    char input[256];
    printf("Enter an input (\"quit\" to quit): ");
    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline
        if (strcmp(input, "quit") == 0) {
            break;
        }
        bool result = NFA_run(nfa, input);
        printf("Result for input \"%s\": %s\n", input, result ? "true" : "false");

        printf("Enter an input (\"quit\" to quit): ");
    }
}
NFA NFA_for_ends_with_at(void) {
    NFA nfa = newNFA(3); // There are 3 states in the NFA

    //State 0
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'a', 1);

    //State 1
    NFA_add_transition_all(nfa, 1, 0);
    NFA_add_transition(nfa, 1, 't', 2);

    // State 2: 'at' found
    NFA_set_accepting(nfa, 2, true);

    return nfa;
}


NFA NFA_for_contains_got(void) {
    NFA nfa = newNFA(4);
    NFA_set_accepting(nfa, 3, true);

    // State 0: Initial state, loop on all characters except 'g'
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'g', 1);

    // State 1: 'g' found, can loop on all characters except 'o'
    NFA_add_transition_all(nfa, 1, 0);
    NFA_add_transition(nfa, 1, 'o', 2);

    // State 2: 'go' found, can loop on all characters except 't'
    NFA_add_transition_all(nfa, 2, 0);
    NFA_add_transition(nfa, 2, 't', 3);

    // State 3: 'got' found, can loop on all characters
    NFA_add_transition_all(nfa, 3, 3);

    return nfa;
}

NFA NFA_for_multiple_characters(void) {
    NFA nfa = newNFA(17);
    NFA_set_accepting(nfa, 8, true);
    NFA_set_accepting(nfa, 9, true);
    NFA_set_accepting(nfa, 10, true);
    NFA_set_accepting(nfa, 11, true);
    NFA_set_accepting(nfa, 12, true);
    NFA_set_accepting(nfa, 15, true);
    NFA_set_accepting(nfa, 16, true);

    //State 0: Initial State
    NFA_add_transition_all(nfa, 0 , 0);
    NFA_add_transition(nfa, 0, 'a', 1);
    NFA_add_transition(nfa, 0, 'e', 2);
    NFA_add_transition(nfa, 0, 'g', 3);
    NFA_add_transition(nfa, 0, 'h', 4);
    NFA_add_transition(nfa, 0, 'i', 5);

    NFA_add_transition(nfa, 0, 'n', 6);
    NFA_add_transition(nfa, 0, 'p', 7);


    //State 1: 1 a found

    NFA_add_transition_all(nfa, 1,1);
    NFA_add_transition(nfa, 1, 'a', 8);


    //State 2: 1 e found
    NFA_add_transition_all(nfa, 2,2);
    NFA_add_transition(nfa, 2, 'e', 9);


    //State 3: 1 g found
    NFA_add_transition_all(nfa, 3,3);
    NFA_add_transition(nfa, 3, 'g', 10);



    //State 4: 1 h found
    NFA_add_transition_all(nfa, 4,4);
    NFA_add_transition(nfa, 4, 'h', 11);



    //State 5: 1 i found
    NFA_add_transition_all(nfa, 5,5);
    NFA_add_transition(nfa, 5, 'i', 12);



    //State 6: 1 n found
    NFA_add_transition_all(nfa, 6,6);
    NFA_add_transition(nfa,6, 'n', 13);


    //State 7: 1 p found
    NFA_add_transition_all(nfa, 7,7);
    NFA_add_transition(nfa,7, 'p', 14);


    //State 8: 2 a found
    NFA_add_transition_all(nfa, 8,8);
    //State 9: 2 e found
    NFA_add_transition_all(nfa, 9,9);
    //State 10: 2 g found
    NFA_add_transition_all(nfa, 10,10);
    //State 11: 2 h found
    NFA_add_transition_all(nfa, 11,11);
    //State 12: 2 i found
    NFA_add_transition_all(nfa, 12,12);

    //State 13: 2 n found
    NFA_add_transition_all(nfa, 13,13);
    NFA_add_transition(nfa,13, 'n', 15);


    //State 14: 2 p found
    NFA_add_transition_all(nfa, 14,14);
    NFA_add_transition(nfa,14, 'p', 16);


    //State15: +2 n found
    NFA_add_transition_all(nfa, 15,15);
    //State16: +2 p found
    NFA_add_transition_all(nfa, 16,16);

    return nfa;
}

int main(void) {


    //DFA Tests
    printf("Testing DFA that recognizes exactly \"CSC\" (capitalized)...\n");
    DFA dfa1 = DFA_for_CSC();
    DFA_repl(dfa1);
    freeDFA(dfa1);

    printf("\nTesting DFA that recognizes strings containing \"end\"...\n");
    DFA dfa2 = DFA_for_contains_end();
    DFA_repl(dfa2);
    freeDFA(dfa2);

    printf("\nTesting DFA that recognizes strings starting with a vowel...\n");
    DFA dfa3 = DFA_for_starts_with_vowel();
    DFA_repl(dfa3);
    freeDFA(dfa3);

    printf("\nTesting DFA that recognizes binary input with an even number of 0's and 1's...\n");
    DFA dfa4 = DFA_for_even_binary();
    DFA_repl(dfa4);
    freeDFA(dfa4);


    //NFA Tests
    printf("\nTesting NFA for strings ending in \"at\"...\n");
    NFA nfa = NFA_for_ends_with_at();
    NFA_repl(nfa);
    freeNFA(nfa);

    printf("\nTesting NFA for strings containing \"got\" anywhere...\n");
    NFA nfa1 = NFA_for_contains_got();
    NFA_repl(nfa1);
    freeNFA(nfa1);


    printf("\nTesting NFA for strings containing more than one a, e, h, i, or g, or more than two n’s or p’s...\n");
    NFA nfa2 = NFA_for_multiple_characters();
    NFA_repl(nfa2);
    freeNFA(nfa2);


    // Convert the NFA to DFA

    printf("\nConverting NFA for strings ending in \"at\"... to a DFA");
    NFA nfa_at_to_convert = NFA_for_ends_with_at();
    DFA dfa_at = nfa_to_dfa(nfa_at_to_convert);
    printf("\n");
    DFA_printStates(dfa_at);
    DFA_repl(dfa_at);
    freeDFA(dfa_at);

    printf("\nConverting NFA for strings containing \"got\"... to a DFA");
    NFA nfa_got_to_convert = NFA_for_contains_got();
    DFA dfa_got = nfa_to_dfa(nfa_got_to_convert);
    printf("\n");
    DFA_printStates(dfa_got);
    DFA_repl(dfa_got);
    freeDFA(dfa_got);


    printf("\nConverting NFA for strings containing more than one a, e, h, i, or g, or more than two n’s or p’s...");
    NFA nfa_multi_to_convert = NFA_for_multiple_characters();
    DFA dfa_multi = nfa_to_dfa(nfa_multi_to_convert);
    printf("\n");
    DFA_printStates(dfa_multi);
    DFA_repl(dfa_multi);
    freeDFA(dfa_multi);

    return 0;
}

