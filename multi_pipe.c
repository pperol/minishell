#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define FATAL "fatal error\n"

void	put_error(char *str)
{
	ft_pustr_fd(str, 2);
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
		if (ft_strcmp(av[i], "|") == 0 || ft_strcmp(av[i], ";") == 0)
			return (i);
		i++;
	}
	return (i);
}

int	is_pipe_next(char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], "|") == 0)
			return (1);
		if (ft_strcmp(av[i], ";") == 0)
			return (0);
		i++;
	}
	return (0);
}

/*******************************************************/

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
