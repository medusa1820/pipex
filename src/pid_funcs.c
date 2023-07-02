/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:12:22 by musenov           #+#    #+#             */
/*   Updated: 2023/07/02 17:23:32 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(t_pipex *data, char **envp)
{
	if (data->pid == 0)
	{
		dup2(data->fd_infile, STDIN_FILENO);
		dup2(data->pipe0_fd[1], STDOUT_FILENO);
		close_pipe0_fds(data);
		close(data->fd_infile);
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(126, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	close(data->fd_infile);
}

void	middle_cmd(t_pipex *data, char **envp, int i)
{
	if (data->pid == 0)
	{
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
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(126, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	if (i % 2 == 0)
		close_pipe1_fds(data);
	else
		close_pipe0_fds(data);
}

void	last_cmd(t_pipex *data, char **envp, int i)
{
	if (data->pid == 0)
	{
		if (i % 2 == 0)
			dup2(data->pipe1_fd[0], STDIN_FILENO);
		else
			dup2(data->pipe0_fd[0], STDIN_FILENO);
		dup2(data->fd_outfile, STDOUT_FILENO);
		close_pipe0_fds(data);
		close_pipe1_fds(data);
		close(data->fd_outfile);
		if (execve(data->cmd_path, data->cmd_split, envp) == -1)
			exit_error(126, "Couldn't execute execve()", data);
		free_all(data);
		// exit(0);
	}
	close(data->fd_outfile);
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
