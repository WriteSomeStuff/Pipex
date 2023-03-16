/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filecheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:05:55 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/16 18:14:14 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// does infile exist? permissions? If so process command, send to outfile.
// pipex should also handle that you can use both relative and absolute paths, access?
// what if awk is used with ""?

// void	*wrapper(void *ptr)
// {
// 	if (ptr)
// 		return (ptr);
// 	else
// 		ft_throwerror;
// }

void	ft_throwerror(char *message, int32_t ernr)
{
	perror(message);
	exit(ernr);
}

void	ft_findexec(char **argv, char **envp)
{
	int		i;
	char	**path;
	char	*temp;
	char	*cmdpath;
	char	**cmd;

	i = 0;
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		ft_throwerror("split error", EXIT_FAILURE);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
		}
		i++;
	}
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
		{
			ft_throwerror("strjoin error temp", EXIT_FAILURE);
		}
		cmdpath = ft_strjoin(temp, cmd[0]);
		if (!cmdpath)
		{
			free(temp);
			ft_throwerror("strjoin error cmdpath", EXIT_FAILURE);
		}
		free(temp);
		if (access(cmdpath, F_OK) == 0)
		{
			if (execve(cmdpath, cmd, envp) == -1)
				ft_throwerror("exec error", errno);
		}
		i++;
	}
}

void	ft_filecheck(int32_t argc, char **argv, char **envp)
{
	int		fd[2]; // for pipe, fd[0] - read, fd[1] - write
	int		fdin; // file1 becoming stdin fileno
	int		fdout; // file2 becoming stdout fileno
	char	*ans; // string to store answer read from file2
	pid_t	pid;

	fdin = 0;
	fdout = 0;
	ans = "replace me";
	if (pipe(fd) == -1)
		ft_throwerror("pipe error", errno);
	pid = fork();
	if (pid == -1)
		ft_throwerror("fork error", errno);
	if (pid == 0)
	{
		fdin = open(argv[1], O_RDONLY);
		if (fdin == -1)
			ft_throwerror("child fdin error", errno);
		if (dup2(fdin, STDIN_FILENO) == -1 || close(fdin) == -1)
			ft_throwerror("child fdin error", errno);
		fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdout == -1)
			ft_throwerror("child fdout error", errno);
		if (dup2(fdout, STDOUT_FILENO) == -1 || close(fdout) == -1)
			ft_throwerror("child fdout error", errno);
		ft_findexec(argv, envp);
	}
	else
	{
		wait(&pid);
		fdout = open(argv[4], O_RDONLY);
		if (fdout == -1)
			ft_throwerror("parent fdout error", errno);
		while (ans)
		{
			ans = get_next_line(fdout);
			if (ans)
				ft_putstr_fd(ans, STDOUT_FILENO);
		}
		if (close(fdout) == -1)
			ft_throwerror("parent fdout error", errno);
	}
	argc = 0;
	close(fd[0]);
	close(fd[1]);
}
