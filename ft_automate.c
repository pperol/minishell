#include "minishell.h"

// Initialise l'automate fini complet
t_automat *init_automat(size_t n_states, size_t n_transit, int init_st, size_t* accept_sts)
{
  t_automat *automaton;
  size_t  i;
  size_t  j;

  automaton = (t_automat *)malloc(sizeof(t_automat));
  automaton->num_states = n_states;
  automaton->num_transitions = n_transit;
  automaton->initial_state = init_st;
  automaton->accepting_states = accept_sts;
  automaton->transitions = (t_transit **)malloc(n_states * sizeof(t_transit *));
  i = 0;
  while (i < n_states)
  {
    automaton->transitions[i] = (t_transit *)malloc(ALPHABET * sizeof(t_transit));
    j = 0;
    while (j < ALPHABET)
    {
      automaton->transitions[i][j].to_state = NOT_FOUND;
      j++;
    }
    i++;
  }
  return (automaton);
}

// Ajoute une transition à l'automate
void add_transition(t_automat *automaton, size_t from_state, int to_state, char symbol) 
{
  int symbol_index;

  symbol_index = symbol - 'a';
  automaton->transitions[from_state][symbol_index].to_state = to_state;
  automaton->transitions[from_state][symbol_index].symbol = symbol;
}

// Vérifie si un mot est reconnu par l'automate
bool recognize(t_automat *automaton, char* word) 
{
  int     state;
  size_t  word_len;
  int     symbol_index;
  size_t  i;

  state = automaton->initial_state;
  //word_len = ft_strlen(word);
  word_len = strlen(word);
  i = 0;
  while (i < word_len)
  {
    symbol_index = word[i] - 'a';
    state = automaton->transitions[state][symbol_index].to_state;
    if (state == NOT_FOUND)
      return false;
    i++;
  }
  i = 0;
  while (i < automaton->num_states) 
  {
    if (automaton->accepting_states[i] == (size_t)state)
      return true;
    i++;
  }
  return false;
}

// Libère la mémoire allouée pour l'automate
void free_automaton(t_automat *automaton) 
{
  size_t i;
  
  i = 0;
  while (i < automaton->num_states)
  {
    free(automaton->transitions[i]);
    i++;
  }
  free(automaton->transitions);
  //free(automaton->accepting_states);
  free(automaton);
}
