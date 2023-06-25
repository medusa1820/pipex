/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:02:04 by musenov           #+#    #+#             */
/*   Updated: 2023/06/25 20:56:43 by musenov          ###   ########.fr       */
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
	char	*cmd1;
	char	*cmd2;
	char	**cmd1_args;
	char	**paths;
	char	*cmd_path;
}	t_pipex;

// pipex.c
int		main(int argc, char **argv, char **envp);

// assign_input.c
void	assign_input(char **argv, t_pipex *data);
char	*find_cmd_path(t_pipex *data, char **envp);

//exit_error_free.c
void	free_2d_str_func(char **str);
void	free_2d_str(t_pipex *data);
void	free_str(t_pipex *data);
void	free_all(t_pipex *data);
void	exit_error(int exit_code, char *error_msg, t_pipex *data);

// get_next_line.c
char	*get_next_line(int fd);

#endif