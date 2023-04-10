/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:55:36 by aahrach           #+#    #+#             */
/*   Updated: 2023/04/10 13:31:12 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, int len, int x)
{
	char	*p;
	int		i;

	if (start > len)
		return (NULL);
	p = malloc((len - start + 2) * sizeof(char));
	if (!p)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (start <= len)
		p[i++] = s[start++];
	if (x == 1)
		free(s);
	p[i] = '\0';
	if (p[0] == '\0')
	{
		free(p);
		return (NULL);
	}
	return (p);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*ft_free(char *buf, char **p)
{
	free(*p);
	*p = NULL;
	free(buf);
	return (NULL);
}

char	*ft_read(int fd, char **p, char *buf)
{
	char	*new;
	int		len;
	int		i;

	new = NULL;
	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
			return (ft_free(buf, p));
		buf[len] = '\0';
		*p = ft_strjoin(*p, buf);
		i = check_line(*p);
		if (i != -1)
		{
			new = ft_substr(*p, 0, i, 0);
			*p = ft_substr(*p, i + 1, ft_strlen(*p), 1);
			free (buf);
			return (new);
		}
	}
	new = ft_substr(*p, 0, ft_strlen(*p), 0);
	ft_free(buf, p);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*p;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	return (ft_read(fd, &p, buf));
}
