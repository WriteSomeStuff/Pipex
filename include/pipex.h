/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/09 14:06:19 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/16 16:28:55 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/types.h>

void	ft_filecheck(int32_t argc, char **argv, char **envp);

#endif