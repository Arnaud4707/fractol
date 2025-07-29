/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <amugisha6@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:11 by amugisha          #+#    #+#             */
/*   Updated: 2024/11/18 22:23:17 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while ((i < n - 1) && s1[i] == s2[i] && s1[i])
		i++;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}
/*
int	main(void)
{
	char	e[] = "abcdef";
	char	f[] = "abddef";

	printf("%d\n%d", strncmp(e, f, 3), ft_strncmp(e, f, 3));
	return (0);
}*/
