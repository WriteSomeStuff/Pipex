/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:43:45 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/22 13:12:52 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 * 
 * @param s1 
 * @param set 
 * @return Char* to the trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	front;
	size_t	back;
	char	*p;

	front = 0;
	back = ft_strlen(s1);
	if (!*s1)
		return (ft_strdup(""));
	while (s1[front] && ft_strchr(set, s1[front]))
	{
		front++;
	}
	while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
	{
		back--;
	}
	p = (char *)malloc(sizeof(char) * (back - front + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, &s1[front], back - front + 1);
	return (p);
}

// int	main(void)
// {
// 	const char *s1 = "daabaacaremove badc somethingaacabad";
// 	const char *set = "abcd";
// 	char *ans = ft_strtrim(s1, set);

// 	printf("%s", ans);
// 	// system("leaks a.out");
// }