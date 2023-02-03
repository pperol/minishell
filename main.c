/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:56:56 by pperol            #+#    #+#             */
/*   Updated: 2023/02/03 18:50:52 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1. 	Reads its input from a file (see Shell Scripts), from a string supplied 
	as an argument to the -c invocation option (see Invoking Bash), or from 
	the user’s terminal.
	Main loop:
	On commence par faire une boucle dans laquelle on lit STDIN 
	Le programme affiche un prompt et stocke l’entrée de l’utilisateur 
	en boucle. 
	On envoie EOF (Ctrl+D) à minishell pour quitter.
	lib : readline, get_next_line, 

	auto :  
		--- libft
		--- readline
		--- rl_clear_history
		--- rl_on_new_line,
		--- rl_replace_line
		--- rl_redisplay
		--- add_history,
		--- printf
		--- malloc
		--- free
		--- write
		--- access
		--- open
		--- read
		--- close 
		--- fork
		--- wait
		--- waitpid
		--- wait3
		--- wait4
		--- signal
		--- sigaction
		--- sigemptyset
		--- sigaddset
		--- kill
		--- exit
		---	getcwd
		--- chdir
		--- stat
		--- lstat
		--- fstat
		--- unlink
		--- execve
		---	dup
		--- dup2
		--- pipe
		--- opendir
		--- readdir
		--- closedir,
		--- strerror
		--- perror
		
		--- isatty : 	int 	isatty(int fd); !!
		--- ttyname : 	char 	*ttyname(int fd);
		--- ttyslot :	int 	ttyslot(void);
		--- ioctl : 	int 	ioctl(int fd, unsigned long request, ...);  #include <sys/ioctl.h>
       
		--- getenv :	char 	*getenv(const char *name);
		
	termios :
	#include <termios.h>
		--- tcgetattr : int 	tcgetattr(int fd, struct termios *termios_p);
		--- tcsetattr : int 	tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
	termcap :
	#include <curses.h>
	#include <term.h> 
		--- tgetent : 	int 	tgetent(char *bp, const char *name);
		--- tgetflag : 	int 	tgetflag(const char *id);
		---	tgetnum : 	int 	tgetnum(const char *id);
		--- tgetstr : 	char 	*tgetstr(const char *id, char **area);
			You can use tgetstr to quesry the terminal database to figure out what they are, 
			or just hardcode your shell to use the ANSI sequences which are what almost all 
			terminals you will see these days use.
		--- tgoto : 	char 	*tgoto(const char *cap, int col, int row);
		--- tputs : 	int 	tputs(const char *str, int affcnt, int (*putc)(int));
*/

void	ft_prompt(void)
{
	write(1, "mini$ ", 6);
}

void	ft_exit(void)
{
	write(1, "exit \n", 6);
}

static void	ft_err_not_found(char *input)
{
		printf("minishell: command not found: %s\n", input);
}

int main(void) {
	char*	input;
	char*	exit;
	
	exit = "exit";
	while (1)
	{
		while ((input = readline("mini$ "))) 
		{
			if (strcmp(input, exit) == 0)
			{
				ft_exit();
				return (0);
			}
			else
				ft_err_not_found(input);
			// permet à l'utilisateur de naviguer avec les flèches haut et bas
			add_history(input);
		}
		ft_exit();
		free(input);
		return (0);
	}
}


/*
2. 	Breaks the input into words and operators, obeying the quoting rules 
	described in Quoting. These tokens are separated by metacharacters. 
	Alias expansion is performed by this step (see Aliases).
*/ 

/*
3. 	Parses the tokens into simple and compound commands (see Shell Commands).
*/ 

/*
4. 	Performs the various shell expansions (see Shell Expansions), breaking 
	the expanded tokens into lists of filenames (see Filename Expansion) and 
	commands and arguments.
*/ 

/*
5. 	Performs any necessary redirections (see Redirections) and removes the 
	redirection operators and their operands from the argument list.
*/ 

/*
6. 	Executes the command (see Executing Commands).
*/ 

/*
7. 	Optionally waits for the command to complete and collects its exit 
	status (see Exit Status).
*/
