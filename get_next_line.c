/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashamurz <ashamurz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:51:18 by ashamurz          #+#    #+#             */
/*   Updated: 2021/05/17 18:00:08 by ashamurz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
size_t	ft_strlen_line(const char *str)
{
	size_t	i;
	i = 0;
	while (str[i] != '\n')
	{
		i++;
	}
	return (i);
}

int check_line(char **save, char **line)
{
    int i;
    i = ft_strlen_line(*save);
    char *temp;
    if((*save)[i] == '\n')
    {
        *line = ft_substr(*save,0,i);
        temp = ft_strdup((*save) + i + 1);
        free(*save);
        *save = temp;
    }
    else 
    {
        *line = ft_strdup(*save);
        free(*save);
        *save = NULL;
        return 0;
    }
    return 1;
}

int get_next_line(int fd, char **line)
{
    static char *save;
    char *temp;
    char buf[BUFFER_SIZE + 1];
    int byte_read;

    byte_read = read(fd, buf, BUFFER_SIZE);
    while(byte_read > 0)
    {
        buf[byte_read] = '\0';
        if (save == NULL)
            save = ft_strdup("");
        temp = ft_strjoin(save,buf);
        free(save);
        save = temp;
        if (ft_strchr(buf, '\n'))
            break;
        byte_read = read(fd, buf, BUFFER_SIZE);       
    }
    return check_line(&save, line);
}

int main()
{
    int fd;
    int i;
    i = 0;
    char *line;
    fd = open("text", O_RDONLY);
    while(i < 3)
    {
        get_next_line(fd, &line);
        printf("%s\n", line);
        i++;   
    }
    return 0;
}
