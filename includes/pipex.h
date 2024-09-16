/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 22:14:36 by gcozigon          #+#    #+#             */
/*   Updated: 2023/07/11 15:16:33 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utils/ft_printf/ft_printf.h"
# include "../utils/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_all
{
	char	**env;
	char	**path;
	int		infile;
	int		outfile;
	int		prev;
	int		here_doc;
	int		pipe_fd[2];
	int		pid[1024];
	char	*path_cmd1;
	int		nbcmd;
	int		flag;
	char	*fileout;
}			t_all;

char		**keep_path(t_all *all);
void		ft_free_split(char **tab);
int			clean_args(t_all *all, char **av);
int			pipex(t_all *all, char **av);
void		open_av(t_all *all, char **av, int i, char **cmd_args);
char		*keep_access(t_all *all, int nb, char *cmd);
void		ft_check_acces(char *path, char *cmd_name);
char		*check_relative_paths(t_all *all, char **cmd_split);
char		*check_absolute_path(char **cmd_split);
char		*generate_test_path(char *path, char *cmd);
void		ft_exec(t_all *all, int nb, char **tmp);
void		free_split(char **tab);
void		close_pipes(t_all *all);
void		free_resources(t_all *all);
void		ft_wait(t_all *all);
int			here_doc(t_all *all, char **av);
int			open_error(t_all *all, char **cmd_args);
char		*ft_strjoingnl(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
#endif
