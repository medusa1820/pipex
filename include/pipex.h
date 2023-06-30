/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:02:04 by musenov           #+#    #+#             */
/*   Updated: 2023/06/30 20:22:53 by musenov          ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	char	*cmd0;
	char	*cmd1;
	int		pipe0_fd[2];
	int		pipe1_fd[2];
	char	**cmd0_args;
	char	**cmd1_args;
	char	**paths;
	char	*cmd_path;
	int		nr_of_cmds;
	pid_t	pid0;
	pid_t	pid1;
}	t_pipex;

// pipex.c
int		main(int argc, char **argv, char **envp);

// assign_input.c
void	init_data(char **argv, t_pipex *data, int argc);
void	pipe_and_fork_0(t_pipex *data);
void	pipe_and_fork_1(t_pipex *data);
void	find_cmd_path_0(t_pipex *data, char **envp);
void	find_cmd_path_1(t_pipex *data, char **envp);
void	main_exec(t_pipex *data, int i, char **envp, char **argv, int argc);

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

#endif