/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashamurz <ashamurz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:51:18 by ashamurz          #+#    #+#             */
/*   Updated: 2021/05/25 19:56:39 by ashamurz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
size_t	ft_strlen_line(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	check_line(char **save, char **line)
{
	int		i;
	char	*temp;

	i = ft_strlen_line(*save);
	if ((*save)[i] == '\n')
	{
		*line = ft_substr(*save, 0, i);
		temp = ft_strdup((*save) + i + 1);
		free(*save);
		*save = temp;
	}
	else
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (0);
	}
	return (1);
}

int	ft_protection(char **save, char **line, int byte_read)
{
	if (byte_read < 0)
		return (-1);
	else if (*save == NULL && byte_read == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (check_line(save, line));
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*temp;
	char		buf[BUFFER_SIZE + 1];
	int			byte_read;

	byte_read = read(fd, buf, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buf[byte_read] = '\0';
		if (save == NULL)
			save = ft_strdup("");
		temp = ft_strjoin(save, buf);
		free(save);
		save = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		byte_read = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_protection(&save, line, byte_read));
}
