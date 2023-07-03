/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:12:22 by musenov           #+#    #+#             */
/*   Updated: 2023/07/03 22:31:21 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(t_pipex *data, char **envp, char **argv)
{
	if (data->pid == 0)
	{
		data->fd_infile = open(argv[1], O_RDONLY);
		if (data->fd_infile < 0)
			exit_error(errno, "Error openning file", data);
		find_cmd_path_0(data, envp);
		dup2(data->fd_infile, STDIN_FILENO);
		dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		close(data->fd_infile);
		// close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	// close(data->fd_infile);
}

void	middle_cmd(t_pipex *data, char **envp, int i)
{
	if (data->pid == 0)
	{
		find_cmd_path_0(data, envp);
		if (i % 2 == 0)
		{
			dup2(data->pipe1_fd[0], STDIN_FILENO);
			dup2(data->pipe0_fd[1], STDOUT_FILENO);
		}
		else
		{
			dup2(data->pipe0_fd[0], STDIN_FILENO);
			dup2(data->pipe1_fd[1], STDOUT_FILENO);
		}
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		// close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	if (i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

void	last_cmd(t_pipex *data, char **envp, int i, char **argv)
{
	if (data->pid == 0)
	{
		data->fd_outfile = open(argv[data->nr_of_cmds + 2], \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (data->fd_outfile < 0)
			exit_error(errno, "Error openning file", data);
		find_cmd_path_0(data, envp);
		if (i % 2 == 0)
			dup2(data->pipe1_fd[0], STDIN_FILENO);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(errno, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	// close(data->fd_outfile);
	close_pipe0_fds(data);
	close_pipe1_fds(data);
}

void	close_pipe0_fds(t_pipex *data)
{
	close(data->pipe0_fd[0]);
	close(data->pipe0_fd[1]);
}

void	close_pipe1_fds(t_pipex *data)
{
	close(data->pipe1_fd[0]);
	close(data->pipe1_fd[1]);
}
