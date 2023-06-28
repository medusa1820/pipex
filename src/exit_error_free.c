/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:34:26 by musenov           #+#    #+#             */
/*   Updated: 2023/06/28 21:13:58 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d_str_func(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
}

void	free_2d_str(t_pipex *data)
{
	if (data->cmd1_args != NULL)
		free_2d_str_func(data->cmd1_args);
	if (data->paths != NULL)
		free_2d_str_func(data->paths);
}

void	free_str(t_pipex *data)
{
	if (data->cmd_path != NULL)
		free(data->cmd_path);
}

void	free_all(t_pipex *data)
{
	free_str(data);
	free_2d_str(data);
}

void	exit_error(int exit_code, char *error_msg, t_pipex *data)
{
	// (void)exit_code;
	perror(error_msg);
	free_all(data);
	// close_in_out_file_fds(data);
	// close_pipe_fds(data);
	exit(exit_code);
}

// void	close_in_out_file_fds(t_pipex *data)
// {
// 	if (data->fd_infile != -1)
// 		close(data->fd_infile);
// 	if (data->fd_outfile != -1)
// 		close(data->fd_outfile);
// }

// void	close_pipe_fds(t_pipex *data)
// {
// 	if (data->pipe_fd[0] != -1)
// 		close(data->pipe_fd[0]);
// 	if (data->pipe_fd[1] != -1)
// 		close(data->pipe_fd[1]);
// }
