/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state_machine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:53:30 by pperol            #+#    #+#             */
/*   Updated: 2023/03/03 14:21:23 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Each state is represented by a state struct that contains function pointers 
for the state's action and transition functions. The current_state variable 
points to the current state's state struct. The transition functions take 
the user input as an argument and return an integer that indicates whether 
the state should transition to a new state (-1), stay in the current state (0), 
or transition to the next state (1).
*/

#include <minishell.h>

void waiting_for_input(struct t_shell_state *state) 
{
	char 	*input;
		
	input = readline("mini$ ");
	if (!input)
		break ;

    // Read user input
    state->input = read_input();

    // Transition to processing_input state
    state->state_fn = processing_input;
}

void processing_input(struct ShellState* state) {
    // TODO: parse and validate user input

    // Transition to executing_command state
    state->state_fn = executing_command;
}

void executing_command(struct ShellState* state) {
    // TODO: launch child process to run command

    // Transition to displaying_output state
    state->state_fn = displaying_output;
}

void displaying_output(struct ShellState* state) {
    // TODO: print output from child process

    // Transition back to waiting_for_input state
    free(state->input);
    state->input = NULL;
    state->state_fn = waiting_for_input;
}

char* read_input() {
    char* input = NULL;
    size_t input_size = 0;
    getline(&input, &input_size, stdin);
    return input;
}

void free_state(struct ShellState* state) {
    if (state) {
        if (state->input) {
            free(state->input);
        }
        free(state);
    }
}

/*test*/
/*

int main() 
{
	// Initialize state
	t_shell_state* state;

	state = malloc(sizeof(t_shell_state));
	state->state_ft = waiting_for_input;
	state->input = NULL;

	// Main loop
	while (1) 
        state->state_fn(state);
	// Clean up
	free_state(state);
	return (0);
}

*/
