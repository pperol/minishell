/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:56:56 by pperol            #+#    #+#             */
/*   Updated: 2023/02/10 14:43:11 by pperol           ###   ########.fr       */
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

void	ft_err_not_found(char *input)
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

Cette fonction permet d'extraire, un à un, tous les éléments syntaxiques (les tokens) 
d'une chaîne de caractères. 
Pour contrôler ce qui doit être extrait, vous devez spécifier l'ensemble des caractères 
pouvant faire office de séparateurs de tokens.

Pour extraire tous les tokens, vous devez invoquer autant de fois que nécessaire la fonction 
strtok. 
Lors du premier appel vous devez passer la chaîne à découper ainsi que la liste des séparateurs. 
En retour, vous récupérerez le premier token. 
Ensuite, vous ne devrez plus repasser la chaîne à découper. 
A la place, il faudra fournir un pointeur nul (NULL) et vous récupérerez le token suivant.

l'utilisation de cette fonction peut s'avérer être dangereuse ! 
Si vous l'utilisez, il faut savoir que :
La chaîne de caractères à découper, ne doit pas être constante car elle est modifiée à 
chaque appel à la fonction strtok.

Comme nous venons de le dire, à la fin de l'extraction, vous ne pouvez plus exploiter 
le contenu du premier paramètre car la chaîne d'origine a été altérée.

La fonction strtok n'est pas « thread-safe ». 
Cela veut dire qu'elle ne doit pas être utilisée en parallèle par plusieurs threads
car elle utilise un unique pointeur vers la chaîne à découper pour les rappels 
suivants (une variable locale statique).

Paramètres
string : la chaîne de caractères pour laquelle nous devons sortir la liste des éléments 
syntaxiques (les tokens).
delimiters : la liste des caractères de séparation à utiliser pour le découpage de la 
chaîne principale.
Valeur de retour
Si un token est encore disponible, la fonction strtok renvoie ce nouveau token. 
Dans le cas contraire, la fonction renvoi un pointeur nul (NULL).

Exemple de code
L'exemple de code suivant extrait tous les mots présents dans un chaîne de caractères initiale.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    // La chaine de caractères à traiter.
    char str[] = "- Voici une phrase avec quelques séparateurs ! -";
    // La définitions de séparateurs connus.
    const char * separators = " ,.-!";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
    char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
        // On demande le token suivant.
        strToken = strtok ( NULL, separators );
    }

    return EXIT_SUCCESS;
}
Exemple d'utilisation de fonction strpbrk
la variable strToken est pointeur vers le token en cours d'extraction. 
En fait, on pointe bien à l'intérieur de la chaîne de caractères initiale. 
Il ne faut donc surtout pas chercher à libérer la mémoire ciblée par strToken via 
un appel à la fonction free.
l'instruction char str[] = "- Voici une phrase avec quelques séparateurs ! -"; crée 
une copie de la chaîne de caractères initiale et constante, dans la pile d'exécution 
(la stack, en anglais). 
Il ne faut surtout pas remplacer cette instruction par char * str = "- Voici une phrase 
avec quelques séparateurs ! -"; : la zone de mémoire pointée serait constante et la 
fonction strtok planterait systématiquement (« segmentation fault » sous Linux/Unix).
Et voici le résultat produit par cet exemple :

$> gcc -o sample sample.c
$> ./sample
Voici
une
phrase
avec
quelques
séparateurs
ulimit -v 2750; 
$>

*/

char	*ft_strtok(char *str, const char *delim)
{
	char	*str_token;
	
	str_token = NULL;
	if (str)
		str_token = str;
	if (!str_token)
		return (NULL);
	//while (*str_token && ft_strchr(delim, *str_token))
	while (*str_token && strchr(delim, *str_token))
		str_token++;
	//while (token && !ft_strchr(delim, *str_token))
	while (str_token && !strchr(delim, *str_token))
		str_token++;
	if (!*str_token)
		return (NULL);
	return (str_token);
}

/*
enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, EOF

  else : "Error : unexpected characters"
}

Heredoc : à gérer dans un pipe.
*/

/*
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
		free(input);
		return (0);
	}
}
*/

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
	
}


*/

static int	tok_echo(char *str)
{
	size_t		n_states;
	size_t		n_transit;
	int			init_st;
	size_t		accept_sts[2] = {1, 4};
	t_automat	*automaton;
	char*		character;
	
	character = "echo";
	n_states = 5;
	n_transit = 4;
	init_st = 0;
	automaton = init_automat(n_states, n_transit, init_st, accept_sts);
	add_transition(automaton, 0, 1, 'e');
	add_transition(automaton, 1, 2, 'c');
	add_transition(automaton, 2, 3, 'h');
	add_transition(automaton, 3, 4, 'o');
	if (recognize(automaton, str)) 
		return (1);
	else 
		return (0);
}

static int	tok_space(char *str)
{
	size_t		n_states;
	size_t		n_transit;
	int			init_st;
	size_t		accept_sts[2] = {1, 1};
	t_automat	*automaton;
	char*		character;
	
	character = " ";
	n_states = 2;
	n_transit = 2;
	init_st = 0;
	automaton = init_automat(n_states, n_transit, init_st, accept_sts);
	add_transition(automaton, 0, 1, ' ');
	add_transition(automaton, 1, 1, ' ');
	if (recognize(automaton, str)) 
		return (1);
	else 
		return (0);
}

static int	tok_pipe(char *str)
{
	size_t		n_states;
	size_t		n_transit;
	int			init_st;
	size_t		accept_sts[2] = {0, 1};
	t_automat	*automaton;
	char*		character;
	
	character = "|";
	n_states = 2;
	n_transit = 1;
	init_st = 0;
	automaton = init_automat(n_states, n_transit, init_st, accept_sts);
	add_transition(automaton, 0, 1, '|');
	if (recognize(automaton, str)) 
		return (1);
	else 
		return (0);
}

int main(void) {
	char*	input;
	char*	exit;
	
	exit = "exit";
	while (1)
	{
		while ((input = readline("mini$ "))) 
		{
			//if (strcmp(input, exit) == 0)
			if (strcmp(input, exit) == 0)
			{
				ft_exit();
				return (0);
			}
			else if (tok_echo(input) == 1)
				printf("minishell: \"%s\" is a command\n", input);
			else if (tok_space(input) == 1)
				printf("minishell: \"%s\" is a spacer\n", input);
			else if (tok_pipe(input) == 1)
				printf("minishell: \"%s\" is a pipe\n", input);
			else
				ft_err_not_found(input);
			// permet à l'utilisateur de naviguer avec les flèches haut et bas :
			add_history(input);
		}
		ft_exit();
		free(input);
		return (0);
	}
	//ft_exit();
	//free(input);
}
