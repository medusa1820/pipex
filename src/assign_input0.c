/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/06/30 21:45:38 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(char **argv, t_pipex *data, int argc)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	data->fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_infile < 0 || data->fd_outfile < 0)
		exit_error(2, "Error opening file", data);
	data->infile = argv[1];
	// data->cmd1 = argv[2];
	// data->cmd2 = argv[3];
	data->outfile = argv[argc - 1];
	data->cmd0_args = NULL;
	data->cmd0_args = NULL;
	data->paths = NULL;
	data->cmd_path = NULL;
	data->nr_of_cmds = argc - 3;
}



void	main_exec(t_pipex *data, int i, char **envp, char **argv, int argc)
{
	if (i % 2 == 0)
	{
		data->cmd0 = argv[i + 2];
		find_cmd_path_0(data, envp);
		pipe_and_fork_0(data);
	}
	else
	{
		data->cmd1 = argv[i + 2];
		find_cmd_path_1(data, envp);
		pipe_and_fork_1(data);
	}
	if (i == argc - 4)
	{
		if (i % 2 == 1)
		{
			if (data->pid1 == 0)
			{
				// pipe0
				dup2(data->pipe0_fd[0], STDIN_FILENO);
				close(data->pipe0_fd[0]);
				close(data->pipe0_fd[1]);
				// pipe1
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
				close(data->pipe1_fd[0]);
				close(data->pipe1_fd[1]);
				if (execve(data->cmd_path, data->cmd1_args, envp) == -1)
					exit_error(126, "Couldn't execute execve()", data);
				exit(0);
			}
			close(data->fd_outfile);
			close(data->pipe1_fd[0]);
			close(data->pipe1_fd[1]);
		}
		else
		{
			if (data->pid0 == 0)
			{
				// pipe1
				dup2(data->pipe1_fd[0], STDIN_FILENO);
				close(data->pipe1_fd[0]);
				close(data->pipe1_fd[1]);
				// pipe0
				dup2(data->fd_outfile, STDOUT_FILENO);
				close(data->fd_outfile);
				close(data->pipe0_fd[0]);
				close(data->pipe0_fd[1]);
				if (execve(data->cmd_path, data->cmd0_args, envp) == -1)
					exit_error(126, "Couldn't execute execve()", data);
				exit(0);
			}
			close(data->fd_outfile);
			close(data->pipe0_fd[0]);
			close(data->pipe0_fd[1]);
		}
	}
	else if (i == 0)
	{
		if (data->pid0 == 0)
		{
			dup2(data->fd_infile, STDIN_FILENO);
			close(data->fd_infile);
			close(data->fd_outfile);
			dup2(data->pipe0_fd[1], STDOUT_FILENO);
			close(data->pipe0_fd[0]);
			close(data->pipe0_fd[1]);
			if (execve(data->cmd_path, data->cmd0_args, envp) == -1)
				exit_error(126, "Couldn't execute execve()", data);
			exit(0);
		}
		close(data->fd_infile);
	}
	else
	{
		if (i % 2 == 0)
		{
			if (data->pid0 == 0)
			{
				// pipe1
				dup2(data->pipe1_fd[0], STDIN_FILENO);
				close(data->pipe1_fd[0]);
				close(data->pipe1_fd[1]);
				// pipe0
				dup2(data->pipe0_fd[1], STDOUT_FILENO);
				close(data->pipe0_fd[0]);
				close(data->pipe0_fd[1]);
				if (execve(data->cmd_path, data->cmd0_args, envp) == -1)
					exit_error(126, "Couldn't execute execve()", data);
				exit(0);
			}
			close(data->pipe1_fd[0]);
			close(data->pipe1_fd[1]);
		}
		if (i % 2 == 1)
		{
			if (data->pid1 == 0)
			{
				// pipe0
				dup2(data->pipe0_fd[0], STDIN_FILENO);
				close(data->pipe0_fd[0]);
				close(data->pipe0_fd[1]);
				// pipe1
				dup2(data->pipe1_fd[1], STDOUT_FILENO);
				// dup2(data.fd_outfile, STDOUT_FILENO);
				// close(data.fd_outfile);
				close(data->pipe1_fd[0]);
				close(data->pipe1_fd[1]);
				if (execve(data->cmd_path, data->cmd1_args, envp) == -1)
					exit_error(126, "Couldn't execute execve()", data);
				exit(0);
			}
			close(data->pipe0_fd[0]);
			close(data->pipe0_fd[1]);
		}
	}
}



void	pipe_and_fork_0(t_pipex *data)
{
	if (pipe(data->pipe0_fd) == -1)
		exit_error(errno, "Pipe failed", data);
	data->pid0 = fork();
	if (data->pid0 == -1)
		exit_error(errno, "Fork failed", data);
}

void	pipe_and_fork_1(t_pipex *data)
{
	if (pipe(data->pipe1_fd) == -1)
		exit_error(errno, "Pipe failed", data);
	data->pid1 = fork();
	if (data->pid1 == -1)
		exit_error(errno, "Fork failed", data);
}

void	find_cmd_path_0(t_pipex *data, char **envp)
{
	char	*cmd_path_func;
	int		i;
	char	*temp;

	data->cmd0_args = ft_split(data->cmd0, ' ');
	if (data->cmd0_args == NULL)
		exit_error(4, "data.cmd0 split failed", data);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd0_args[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		free(temp);
		// printf("==================== THIS REACHED ====================\n");
		if (access(cmd_path_func, X_OK) != -1)
		{
			data->cmd_path = cmd_path_func;
			printf("==================== THIS REACHED ====================\n");
			break ;
		}
		free(cmd_path_func);
		i++;
	}
	if (data->paths[i] == NULL)
		exit_error(127, "Command not found", data);
}


void	find_cmd_path_1(t_pipex *data, char **envp)
{
	char	*cmd_path_func;
	int		i;
	char	*temp;

	data->cmd1_args = ft_split(data->cmd1, ' ');
	if (data->cmd1_args == NULL)
		exit_error(4, "data.cmd1 split failed", data);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd1_args[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		free(temp);
		// printf("==================== THIS REACHED ====================\n");
		if (access(cmd_path_func, X_OK) != -1)
		{
			data->cmd_path = cmd_path_func;
			printf("==================== THIS REACHED ====================\n");
			break ;
		}
		free(cmd_path_func);
		i++;
	}
	if (data->paths[i] == NULL)
		exit_error(130, "Command not found", data);
}
