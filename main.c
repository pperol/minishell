/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:56:56 by pperol            #+#    #+#             */
/*   Updated: 2023/02/03 21:10:44 by pperol           ###   ########.fr       */
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

// fonction qui va stocker la commande dans un char ** :

static char	**split(char *raw_cmd, char *limit)
{
	char	*ptr = NULL;
	char	**cmd = NULL;
	size_t	idx = 0;

	// split sur les espaces
	ptr = strtok(raw_cmd, limit);

	while (ptr) {
		cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	// On alloue un element qu'on met a NULL a la fin du tableau
	cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}

static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

// execution :

static void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("minishell");
		exit(EXIT_FAILURE);
	}
}

/*
/// Libft:
La fonction strtok() scinde une chaîne en une séquence d'éléments lexicaux. 
Lors du premier appel à strtok(), la chaîne à scinder doit être spécifiée dans str. 
Dans chaque appel ultérieur fait pour analyser la même chaîne, str doit être NULL.
L'argument delim spécifie l'ensemble des caractères qui délimitent les éléments 
dans la chaîne à analyser. 
La chaîne de séparateurs delimit peut être différente à chaque appel sur la même chaîne.
Chaque appel à strtok() renvoie un pointeur sur une chaîne, terminée par un octet nul, 
contenant l'élément suivant. 
Cette chaîne n'inclut pas le séparateur. 
S'il n'y a plus d'éléments, strtok renvoie NULL.
Une séquence, dans la chaîne à analyser, de deux séparateurs contigus ou plus est considérée 
comme un seul séparateur. 
Les séparateurs en début et en fin de chaîne sont ignorés. 
Les éléments renvoyés par strtok() sont toujours des chaînes non vides.
strtok() renvoie un pointeur sur l'élément lexical suivant, ou NULL s'il n'y en a plus.  
*/

static char	*ft_strtok(char *str, const char *delim)
{
	char	*token;
	
	token = NULL;
	if (str)
		token = str;
	if (!token)
		return (NULL);
	//while (*token && ft_strchr(delim, *token))
	while (*token && strchr(delim, *token))
		token++;
	//while (token && !ft_strchr(delim, *token))
	while (token && !strchr(delim, *token))
		token++;
	if (!*token)
		return (NULL);
	return (token);
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
			// permet à l'utilisateur de naviguer avec les flèches haut et bas :
			add_history(input);
		}
		ft_exit();
		//free(input);
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
