/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/07/03 22:30:42 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(char **argv, t_pipex *data, int argc)
{
	data->nr_of_cmds = argc - 3;
	data->cmd = NULL;
	data->cmd_split = NULL;
	data->paths = NULL;
	data->cmd_path = NULL;
	// data->fd_infile = open(argv[1], O_RDONLY);
	// data->fd_outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// if (data->fd_infile < 0 || data->fd_outfile < 0)
	// 	exit_error(0, "Error openning file", data);
}

void	main_exec(t_pipex *data, int i, char **envp, char **argv)
{
	data->cmd = argv[i + 2];
	// find_cmd_path_0(data, envp);
	if (i % 2 == 0)
	{
		if (pipe(data->pipe0_fd) == -1)
			exit_error(errno, "Pipe failed", data);
	}
	else
	{
		if (pipe(data->pipe1_fd) == -1)
			exit_error(errno, "Pipe failed", data);
	}
	data->pid = fork();
	if (data->pid == -1)
		exit_error(errno, "Fork failed", data);
	if (i == data->nr_of_cmds - 1)
		last_cmd(data, envp, i, argv);
	else if (i == 0)
		first_cmd(data, envp, argv);
	else
		middle_cmd(data, envp, i);
}

void	find_cmd_path_0(t_pipex *data, char **envp)
{
	char	*cmd_path_func;
	int		i;
	char	*temp;

	prepare_paths(data, envp);
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd_split[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		free(temp);
		if (access(cmd_path_func, X_OK) != -1)
		{
			data->cmd_path = cmd_path_func;
			break ;
		}
		free(cmd_path_func);
		i++;
	}
	if (data->paths[i] == NULL)
		exit_error(127, "Command not found", data);
		// exit_error(127, "zsh", data);
}

void	prepare_paths(t_pipex *data, char **envp)
{
	int	i;

	data->cmd_split = ft_split(data->cmd, ' ');
	if (data->cmd_split == NULL)
		exit_error(4, "data.cmd split failed", data);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=/", 6) == 0)
		i++;
	data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
}
