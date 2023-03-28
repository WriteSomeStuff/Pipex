/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   childproc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:05:55 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/28 18:12:05 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_firstcmd(char **argv, t_file *file)
{
	if (close(file->fd1[0]) == -1 || close(file->fd2[0]) == -1 || \
		close(file->fd2[1]) == -1)
		ft_throwerror("close", errno);
	file->fdin = open(argv[1], O_RDONLY);
	if (file->fdin == -1)
		ft_throwerror("input", errno);
	if (dup2(file->fdin, STDIN_FILENO) == -1 || close(file->fdin) == -1)
		ft_throwerror("input", errno);
	if (dup2(file->fd1[1], STDOUT_FILENO) == -1 || close(file->fd1[1]) == -1)
		ft_throwerror("output", errno);
}

static void	ft_middlecmds(t_file *file)
{
	if (close(file->fd1[1]) == -1 || close(file->fd2[0]) == -1)
		ft_throwerror("close", errno);
	if (dup2(file->fd1[0], STDIN_FILENO) == -1 || close(file->fd1[0]) == -1)
		ft_throwerror("input", errno);
	if (dup2(file->fd2[1], STDOUT_FILENO) == -1 || close(file->fd2[1]) == -1)
		ft_throwerror("output", errno);
}

static void	ft_lastcmd(int32_t argc, char **argv, int32_t lastcmd, t_file *file)
{
	if (argc % 2 == 1)
	{
		if (close(file->fd1[1]) == -1 || close(file->fd2[0]) == -1 || \
			close(file->fd2[1]) == -1)
			ft_throwerror("close", errno);
		if (dup2(file->fd1[0], STDIN_FILENO) == -1 || close(file->fd1[0]) == -1)
			ft_throwerror("input", errno);
	}
	else
	{
		if (close(file->fd1[0]) == -1 || close(file->fd1[1]) == -1 || \
			close(file->fd2[1]) == -1)
			ft_throwerror("close", errno);
		if (dup2(file->fd2[0], STDIN_FILENO) == -1 || close(file->fd2[0]) == -1)
			ft_throwerror("input", errno);
	}
	file->fdout = open(argv[lastcmd + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file->fdout == -1)
		ft_throwerror("output", errno);
	if (dup2(file->fdout, STDOUT_FILENO) == -1 || close(file->fdout) == -1)
		ft_throwerror("output", errno);
}

void	ft_makechildren(t_arg *arg, t_file *file, t_id *pid)
{
	int32_t	i;
	int32_t	lastcmd;

	i = 2;
	lastcmd = arg->argc - 2;
	while (i <= lastcmd)
	{
		pid->pid = fork();
		if (pid->pid == -1)
			ft_throwerror("fork error", errno);
		if (pid->pid == 0)
		{
			if (i == 2)
				ft_firstcmd(arg->argv, file);
			else if (i > 2 && i < lastcmd)
				ft_middlecmds(file);
			else if (i == lastcmd)
				ft_lastcmd(lastcmd + 2, arg->argv, lastcmd, file);
			ft_findexec(arg->argv[i], arg->envp);
		}
		i++;
	}
}
