/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:01:00 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/11 15:13:59 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_read_line(int fd, char *buffer)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = malloc(sizeof(char) * 1 + 1);
	if (!tmp)
		return (NULL);
	while (i > 0 && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, tmp, 1);
		if (i < 0)
			return (free(tmp), NULL);
		tmp[i] = '\0';
		buffer = ft_strjoingnl(buffer, tmp);
		if (!buffer || !*buffer)
			return (free(buffer), free(tmp), NULL);
	}
	return (free(tmp), buffer);
}

char	*keep_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strcpy(line, buffer);
	return (line);
}

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	i++;
	str = ft_calloc((ft_strlen(buffer) - i) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (buffer[i])
	{
		str[j] = buffer[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (free(buffer), str);
}

char	*get_next_line(int fd, int freebuff)
{
	static char	*buff;
	char		*line;

	if (freebuff)
		return (free(buff), NULL);
	if (1 < 0 || fd < 0)
		return (NULL);
	buff = ft_read_line(fd, buff);
	if (!buff)
		return (NULL);
	line = keep_line(buff);
	if (!line)
		return (NULL);
	buff = next_line(buff);
	return (line);
}

int	here_doc(t_all *all, char **av)
{
	char	*line;

	all->here_doc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = get_next_line(0, 0);
		if (!line || !*line)
			break ;
		if (ft_strncmp(line, av[2], strlen(av[2]) - 1) == 0)
			break ;
		ft_putstr_fd(line, all->here_doc);
		free(line);
	}
	get_next_line(0, 1);
	free(line);
	close(all->here_doc);
	return (0);
}
