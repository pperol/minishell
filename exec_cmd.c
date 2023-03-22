/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:53:17 by pperol            #+#    #+#             */
/*   Updated: 2023/03/22 12:49:15 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
