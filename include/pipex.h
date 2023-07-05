/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:02:04 by musenov           #+#    #+#             */
/*   Updated: 2023/07/05 14:19:19 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/ft_printf/libft/libft.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		nr_of_cmds;
	int		pipe0_fd[2];
	int		pipe1_fd[2];
	char	*cmd;
	char	**cmd_split; // malloc
	char	**paths; // malloc
	char	*cmd_path; // malloc
	pid_t	pid;
}	t_pipex;

// pipex.c
int		main(int argc, char **argv, char **envp);
// void	init_data(char **argv, t_pipex *data, int argc);
void	init_data(t_pipex *data, int argc);

// assign_input.c
void	main_exec(t_pipex *data, int i, char **envp, char **argv);
void	find_cmd_path_0(t_pipex *data, char **envp);
void	prepare_cmd_split(t_pipex *data);
void	prepare_paths(t_pipex *data, char **envp);
void	prepare_cmd_path(t_pipex *data);
void	prepare_cmd_path_slash(t_pipex *data);

//exit_error_free.c
void	free_2d_str_func(char **str);
void	free_2d_str(t_pipex *data);
void	free_str(t_pipex *data);
void	free_all(t_pipex *data);
void	exit_error(int exit_code, char *error_msg, t_pipex *data);
void	close_in_out_file_fds(t_pipex *data);
void	close_pipe_fds(t_pipex *data);

// get_next_line.c
char	*get_next_line(int fd);

//pid_funcs.c
void	first_cmd(t_pipex *data, char **envp, char **argv);
void	middle_cmd(t_pipex *data, char **envp, int i);
void	last_cmd(t_pipex *data, char **envp, int i, char **argv);
void	close_pipe0_fds(t_pipex *data);
void	close_pipe1_fds(t_pipex *data);

#endif