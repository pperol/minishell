/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:57:21 by pperol            #+#    #+#             */
/*   Updated: 2023/02/05 13:23:11 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include "libft.h"
# include <signal.h>
# include <string.h>

/** COLORS: **/
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RST "\e[0m"

/* Define TOKENS */
# define    T_PIPE 1
# define    T_REDIRECT_IN 2
# define    T_REDIRECT_OUT 3
# define    T_HEREDOC 4
# define    D_REDIRECT_OUT 5
# define    S_QUOTE 6
# define    D_QUOTE 7
# define    T_SPACE 8
# define    T_WORD 9
# define    T_CMD 10

/** ERRORS: **/
# define SYNTAX_ERR_PIPE 1
# define SYNTAX_ERR_REDIRECT_IN 2
# define SYNTAX_ERR_REDIRECT_OUT 3
# define SYNTAX_ERR_D_REDIRECT_OUT 4
# define SYNTAX_ERR_NEWLINE 5
# define SYNTAX_ERR_HEREDOC 6
# define UNCLOSED_QUOTES_ERR 7
# define TAB_OR_SPC_ERR 8

# define MEM_ALLOC_ERR "memory allocation failure"

# define EXIT_CODE_NO_SUCH_FILE_OR_DIR 127
# define EXIT_CODE_COMMAND_NOT_FOUND 127
# define EXIT_CODE_CTRLC_HEREDOC 130

#endif

/* Utils */
void	ft_prompt(void);
void	ft_exit(void);
void	ft_err_not_found(char *input);

/* Libft */
static char	*ft_strtok(char *str, const char *delim);