/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 13:37:00 by cschabra      #+#    #+#                 */
/*   Updated: 2023/03/22 13:12:52 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation
 * of ’s1’ and ’s2’.
 * 
 * @param s1 
 * @param s2 
 * @return Char* to the new string. NULL if the allocation fails.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	char	*p;

	i = 0;
	j = 0;
	slen = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (slen + 1));
	if (!p)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = 0;
	return (p);
}

// int	main(void)
// {
// 	const char	*s1 = "";
// 	const char	*s2 = "abcd";
// 	char *ans = ft_strjoin(s1, s2);

// 	printf("%s", ans);
// 	// system("leaks a.out");
// }
