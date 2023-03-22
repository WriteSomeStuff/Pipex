/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filecheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:05:55 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/22 12:13:45 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// pipex should also handle that you can use both relative and absolute paths, access?
// if awk is used with '' it breaks
// void	*wrapper(void *ptr)
// {
// 	if (ptr)
// 		return (ptr);
// 	else
// 		ft_throwerror;
// }

void	ft_throwerror(char *message, int32_t ernr)
{
	if (ernr == 127)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else
		perror(message);
	exit(ernr);
}

void	ft_findexec(char *argv, char **envp)
{
	int32_t	i;
	char	**path;
	char	*temp;
	char	*cmdpath;
	char	**cmd;

	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_throwerror("split error", EXIT_FAILURE);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			ft_throwerror("strjoin error temp", EXIT_FAILURE);
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
	exit(127);
}

void	ft_filecheck(int32_t argc, char **argv, char **envp)
{
	int32_t	fd1[2]; // for pipe, fd1[0] - read, fd1[1] - write
	int32_t	fd2[2];
	int32_t	fdin;
	int32_t	fdout;
	pid_t	pid;
	int32_t	stat;
	int32_t	statcode;
	int32_t	i;
	int32_t	lastcmd;
	int32_t	pidstat;

	i = 2;
	lastcmd = argc - 2;
	if (pipe(fd1) == -1 || pipe(fd2) == -1)
		ft_throwerror("pipe error", errno);
	while (i <= lastcmd)
	{
		pid = fork();
		if (pid == -1)
			ft_throwerror("fork error", errno);
		printf("%i\n", pid);
		if (pid == 0)
		{
			if (i == 2)
			{
				puts("first cmd child");
				close(fd1[0]);
				close(fd2[0]);
				close(fd2[1]);
				fdin = open(argv[1], O_RDONLY);
				if (fdin == -1)
					ft_throwerror("fdin error", errno);
				if (dup2(fdin, STDIN_FILENO) == -1 || close(fdin) == -1)
					ft_throwerror("fdin error", errno);
				if (dup2(fd1[1], STDOUT_FILENO) == -1 || close(fd1[1]) == -1)
					ft_throwerror("child fdout error", errno);
			}
			else if (i > 2 && i < lastcmd)
			{
				puts("middle cmd child");
				close(fd1[1]);
				close(fd2[0]);
				if (dup2(fd1[0], STDIN_FILENO) == -1 || close(fd1[0]) == -1)
					ft_throwerror("fdin error", errno);
				if (dup2(fd2[1], STDOUT_FILENO) == -1 || close(fd2[1]) == -1)
					ft_throwerror("child fdout error", errno);
			}
			else if (i == lastcmd)
			{
				puts("last cmd child");
				close(fd1[0]);
				close(fd1[1]);
				close(fd2[1]);
				fdout = open(argv[lastcmd + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (fdout == -1)
					ft_throwerror("child fdout error", errno);
				if (dup2(fdout, STDOUT_FILENO) == -1 || close(fdout) == -1)
					ft_throwerror("child fdout error", errno);
				if (dup2(fd2[0], STDIN_FILENO) == -1 || close(fd2[0]) == -1)
					ft_throwerror("fdin error", errno);
			}
			ft_findexec(argv[i], envp);
		}
		sleep(1);
		i++;
	}
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	pidstat = waitpid(pid, &stat, 0);
	printf("%i\n", pidstat);
	if (WIFEXITED(stat))
	{
		statcode = WEXITSTATUS(stat);
		if (statcode != 0)
			ft_throwerror("command not found", statcode);
		exit(statcode);
	}
}
