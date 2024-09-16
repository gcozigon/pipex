/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:02:20 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/10 17:27:00 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_redir(t_all *all, int nb)
{
	if (nb == 0)
	{
		dup2(all->infile, STDIN_FILENO);
		close(all->infile);
	}
	else if (nb == all->nbcmd - 1)
	{
		dup2(all->outfile, STDOUT_FILENO);
		close(all->outfile);
	}
	if (nb != 0)
	{
		dup2(all->prev, STDIN_FILENO);
		close(all->prev);
	}
	if (nb != all->nbcmd - 1)
		dup2(all->pipe_fd[1], STDOUT_FILENO);
	close(all->pipe_fd[0]);
	close(all->pipe_fd[1]);
}

char	*find_cmd(t_all *all, char **cmd_split)
{
	char	*result;

	if (!*cmd_split)
		return (NULL);
	if (ft_strrchr(cmd_split[0], '/'))
	{
		if (!access(cmd_split[0], F_OK | X_OK))
			return (cmd_split[0]);
		return (ft_check_acces(cmd_split[0], cmd_split[0]), NULL);
	}
	result = check_relative_paths(all, cmd_split);
	return (result);
}

int	execute_child_process(t_all *all, char **av, char **cmd_args, int i)
{
	open_av(all, av, i, cmd_args);
	ft_redir(all, i);
	all->path_cmd1 = find_cmd(all, cmd_args);
	if (all->path_cmd1 && cmd_args)
		ft_exec(all, i, cmd_args);
	close_pipes(all);
	free_resources(all);
	free_split(cmd_args);
	exit(126);
}

int	pipex(t_all *all, char **av)
{
	int		i;
	char	**cmd_args;

	i = -1;
	all->prev = -1;
	while (++i < all->nbcmd)
	{
		pipe(all->pipe_fd);
		all->pid[i] = fork();
		if (all->pid[i] == 0)
		{
			cmd_args = ft_split(av[i + 2], ' ');
			if (!cmd_args)
				return (exit(1), 1);
			execute_child_process(all, av, cmd_args, i);
		}
		if (all->prev != -1)
			close(all->prev);
		all->prev = all->pipe_fd[0];
		if (all->pipe_fd[1] > -1)
			close(all->pipe_fd[1]);
	}
	ft_wait(all);
	return (0);
}

void	open_av(t_all *all, char **av, int i, char **cmd_args)
{
	if (i == 0)
	{
		all->infile = open(av[1], O_RDONLY);
		if (all->infile == -1)
		{
			ft_printf("Pipex : %s: No such file or directory\n", av[1]);
			close_pipes(all);
			free_resources(all);
			free_split(cmd_args);
			exit(1);
		}
	}
	else if (i == all->nbcmd - 1)
	{
		all->outfile = open(all->fileout, O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (all->outfile == -1)
		{
			ft_printf("Pipex : %s: No such file or directory\n", all->fileout);
			close_pipes(all);
			close(all->prev);
			free_resources(all);
			free_split(cmd_args);
			exit(1);
		}
	}
}
