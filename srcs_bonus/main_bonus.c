/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:17:28 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/11 15:14:06 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	if (ac < 5)
		return (ft_printf("Pipex : Syntax error near unexpected token : %s\n",
				av[ac - 1]), 1);
	all = ft_calloc(1, sizeof(t_all));
	if (!all)
		return (0);
	all->here_doc = 0;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		here_doc(all, av);
		all->here_doc = 1;
	}
	all->nbcmd = ac - 3 - all->here_doc;
	all->path_cmd1 = av[3];
	all->env = env;
	all->path = keep_path(all);
	all->fileout = av[ac - 1];
	pipex(all, av);
	close_pipes(all);
	free_resources(all);
	return (0);
}

int	open_error(t_all *all, char **cmd_args)
{
	close_pipes(all);
	free_resources(all);
	free_split(cmd_args);
	exit(1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	dest[++i] = '\0';
	return (dest);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		len;
	int		j;

	j = 0;
	i = 0;
	if (!s1)
		return (free(s1), ft_strdup(s2));
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * ((len) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}
