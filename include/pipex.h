/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:06:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/04/05 18:31:35 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct file
{
	int32_t	fd1[2];
	int32_t	fdin;
	int32_t	fdout;
}	t_file;

typedef struct arg
{
	int32_t	argc;
	char	**argv;
	char	**envp;
}	t_arg;

typedef struct id
{
	pid_t	pid;
	int32_t	stat;
	int32_t	statcode;
	int32_t	pidstat;
}	t_id;

void	ft_makechildren(t_arg *arg, t_file *file, t_id *pid);

void	ft_cmdcheck(char *argv);
void	ft_inputcheck(int32_t argc);
void	ft_throwerror(char *message, int32_t ernr);

void	ft_findexec(char *argv, char **envp);

#endif