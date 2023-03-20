/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filecheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:05:55 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/20 15:28:14 by cschabra      ########   odam.nl         */
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

int32_t	ft_getlastcmd(char **argv)
{
	int32_t	i;

	i = 0;
	while(argv[i])
		i++;
	return (i);
}

void	ft_filecheck(int32_t argc, char **argv, char **envp)
{
	int32_t	fd[2]; // for pipe, fd[0] - read, fd[1] - write
	int32_t	fdin; // file1 becoming stdin fileno
	int32_t	fdout; // file2 becoming stdout fileno
	pid_t	pid;
	int32_t	stat;
	int32_t	statcode;
	int32_t	i;
	int32_t	lastcmd;

	i = 2;
	lastcmd = ft_getlastcmd(argv) - 2;
	printf("%i\n", lastcmd);
	fdin = open(argv[1], O_RDONLY);
	if (fdin == -1)
		ft_throwerror("fdin error", errno);
	if (dup2(fdin, STDIN_FILENO) == -1 || close(fdin) == -1)
		ft_throwerror("fdin error", errno);
	fdout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdout == -1)
		ft_throwerror("child fdout error", errno);
	if (dup2(fdout, STDOUT_FILENO) == -1 || close(fdout) == -1)
		ft_throwerror("child fdout error", errno);
	if (pipe(fd) == -1)
		ft_throwerror("pipe error", errno);
	pid = fork();
	if (pid == -1)
		ft_throwerror("fork error", errno);
	if (pid == 0)
	{
		ft_findexec(argv[i], envp);
	}
	i++;
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
	{
		statcode = WEXITSTATUS(stat);
		if (statcode != 0)
			ft_throwerror("command not found", statcode);
	}
		// fdout = open(argv[4], O_RDONLY);
		// if (fdout == -1)
		// 	ft_throwerror("parent fdout error", errno);
		// while (ans)
		// {
		// 	ans = get_next_line(fdout);
		// 	if (ans)
		// 		ft_putstr_fd(ans, STDOUT_FILENO);
		// }
		// if (close(fdout) == -1)
		// 	ft_throwerror("parent fdout error", errno);
	argc = 0;
	close(fd[0]);
	close(fd[1]);
}
