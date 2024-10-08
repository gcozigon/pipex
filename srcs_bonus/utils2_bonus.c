/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 22:06:34 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/10 14:11:42 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(t_all *all, int nb, char **tmp)
{
	if (nb == 0)
	{
		execve(all->path_cmd1, tmp, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(all->path_cmd1, tmp, NULL);
		exit(EXIT_FAILURE);
	}
}

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	close_pipes(t_all *all)
{
	if (all->pipe_fd[0] > -1)
		close(all->pipe_fd[0]);
	if (all->pipe_fd[1] > -1)
		close(all->pipe_fd[1]);
}

void	free_resources(t_all *all)
{
	if (all->path)
		free_split(all->path);
	free(all);
}

void	ft_wait(t_all *all)
{
	int	i;

	i = -1;
	close(all->prev);
	close(all->pipe_fd[0]);
	while (++i < all->nbcmd)
		waitpid(all->pid[i], 0, 0);
}
