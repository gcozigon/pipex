/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:17:28 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/10 20:47:44 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	if (ac < 5)
		return (ft_printf("Pipex : Syntax error near unexpected token : %s\n",
				av[ac - 1]), 1);
	if (ac > 5)
		return (ft_printf("Pipex : Too many arguments\n"), 1);
	all = ft_calloc(1, sizeof(t_all));
	if (!all)
		return (0);
	all->env = env;
	all->path = keep_path(all);
	all->path_cmd1 = av[2];
	all->nbcmd = ac - 3;
	all->fileout = av[ac - 1];
	pipex(all, av);
	close_pipes(all);
	free_resources(all);
	return (0);
}
