#include "minishell.h"

#define ALPHABET_SIZE 26
#define NOT_FOUND -1

// Structure pour stocker les transitions de l'automate
struct Transition {
  int to_state;
  char symbol;
};

// Structure pour stocker un automate fini complet
struct CompleteAutomaton {
  int num_states;
  int num_transitions;
  int initial_state;
  int* accepting_states;
  struct Transition** transitions;
};

// Fonction pour initialiser un automate fini complet
struct CompleteAutomaton* init_complete_automaton(int num_states, int num_transitions, int initial_state, int* accepting_states) {
  struct CompleteAutomaton* automaton = (struct CompleteAutomaton*)malloc(sizeof(struct CompleteAutomaton));
  automaton->num_states = num_states;
  automaton->num_transitions = num_transitions;
  automaton->initial_state = initial_state;
  automaton->accepting_states = accepting_states;
  automaton->transitions = (struct Transition**)malloc(num_states * sizeof(struct Transition*));
  for (int i = 0; i < num_states; i++) {
    automaton->transitions[i] = (struct Transition*)malloc(ALPHABET_SIZE * sizeof(struct Transition));
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      automaton->transitions[i][j].to_state = NOT_FOUND;
    }
  }
  return automaton;
}

// Fonction pour ajouter une transition à un automate fini complet
void add_transition(struct CompleteAutomaton* automaton, int from_state, int to_state, char symbol) {
  int symbol_index = symbol - 'a';
  automaton->transitions[from_state][symbol_index].to_state = to_state;
  automaton->transitions[from_state][symbol_index].symbol = symbol;
}

// Fonction pour vérifier si un mot est reconnu par un automate fini complet
bool recognize(struct CompleteAutomaton* automaton, char* word) {
  int state = automaton->initial_state;
  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++) {
    int symbol_index = word[i] - 'a';
    state = automaton->transitions[state][symbol_index].to_state;
    if (state == NOT_FOUND) {
      return false;
    }
  }
  for (int i = 0; i < automaton->num_states; i++) {
    if (automaton->accepting_states[i] == state) {
      return true;
    }
  }
  return false;
}

// Fonction pour libérer la mémoire allouée pour un automate fini complet
void free_complete_automaton(struct CompleteAutomaton* automaton) {
  for (int i = 0; i < automaton->num_states; i++) {
    free(automaton->transitions[i]);
  }
  free(automaton->transitions);
  free(automaton->accepting_states);
  free(automaton);
}