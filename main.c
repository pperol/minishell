/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:56:56 by pperol            #+#    #+#             */
/*   Updated: 2023/02/02 11:14:52 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

2. 	Breaks the input into words and operators, obeying the quoting rules 
	described in Quoting. These tokens are separated by metacharacters. 
	Alias expansion is performed by this step (see Aliases).

3. 	Parses the tokens into simple and compound commands (see Shell Commands).

4. 	Performs the various shell expansions (see Shell Expansions), breaking 
	the expanded tokens into lists of filenames (see Filename Expansion) and 
	commands and arguments.

5. 	Performs any necessary redirections (see Redirections) and removes the 
	redirection operators and their operands from the argument list.

6. 	Executes the command (see Executing Commands).

7. 	Optionally waits for the command to complete and collects its exit 
	status (see Exit Status).

*/

/*
1. 	Reads its input from a file (see Shell Scripts), from a string supplied 
	as an argument to the -c invocation option (see Invoking Bash), or from 
	the user’s terminal.
	Boucle principale
	On commence par faire une boucle dans laquelle on lit STDIN 
	(la commande de l’user)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main()
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;

	// alloc buffer qui stockera la commande entree par l'user
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	// ecriture d'un prompt
	write(1, "$> ", 3);

	// lecture de STDIN en boucle
	while (getline(&buffer, &buf_size, stdin) > 0) {
		printf("cmd = %s\n", buffer);
		write(1, "$> ", 3);
	}

	printf("Bye \n");
	free(buffer);
}
