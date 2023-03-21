#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define FATAL "fatal error\n"

void	put_error(char *str)
{
	dprintf(2, "%s", str);
}

void	put_error_exit(char *str)
{
	put_error(str);
	exit(1);
}

int	get_next_sep(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (strcmp(av[i], "|") == 0 || strcmp(av[i], ";") == 0)
			return (i);
		i++;
	}
	return (i);
}

int	exec_cd(char **av)
{
	int i;

	i = get_next_sep(av);
	if (i != 2)
		put_error("cd bad arguments\n");
	else if (chdir(av[1]) == -1)
	{
		put_error("can't cd to ");
		put_error(av[1]);
		put_error("\n");
	}
	return (i);
}

int	is_pipe_next(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (strcmp(av[i], "|") == 0)
			return (1);
		if (strcmp(av[i], ";") == 0)
			return (0);
		i++;
	}
	return (0);
}

void exec_child_process(char **av, char **env, int *prev_pipe, int pipe_next)
{
    if (*prev_pipe > 1)
    {
        if (dup2(*prev_pipe, STDIN_FILENO) == -1)
            put_error_exit(FATAL);
    }
    if (pipe_next)
    {
        int fd[2];
        if (pipe(fd) == -1)
            put_error_exit(FATAL);
        if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
            put_error_exit(FATAL);
        *prev_pipe = fd[STDIN_FILENO];
    }
    av[get_next_sep(av)] = NULL;
    if (execve(av[0], av, env) == -1)
    {
        put_error("fail to execute ");
        put_error(av[0]);
        put_error("\n");
    }
    exit(EXIT_FAILURE);
}

void exec_cmd(char **av, char **env, int *prev_pipe)
{
    int pipe_next;
    int pid;

    pipe_next = is_pipe_next(av);
    if ((pid = fork()) == -1)
        put_error_exit(FATAL);
    if (pid == 0)
        exec_child_process(av, env, prev_pipe, pipe_next);
    if (*prev_pipe > 1)
    {
        if (close(*prev_pipe) == -1)
            put_error_exit(FATAL);
        *prev_pipe = 0;
    }
    if (pipe_next)
    {
        if (close(fd[STDOUT_FILENO]) == -1)
            put_error_exit(FATAL);
    }
    waitpid(0, NULL, 0);
}

int main(int ac, char **av, char **env)
{
	int i = 1;
	int prev_pipe = 0;

	if (ac < 2)
		return (0);
	while (av[i])
	{
		while (strcmp(av[i], ";") == 0)
			i++;
		if (!av[i])
			return (0);
		if (strcmp(av[i], "cd") == 0)
		{
			i += exec_cd(av + i);
		}
		else
		{
			exec_cmd(av + i, env, &prev_pipe);
			i += get_next_sep(av + i);
		}
		if (av[i])
			i++;
	}
	return (0);
}

/*


#define	BUFFSIZE	4096

int main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}

*/
