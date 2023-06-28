/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/06/28 21:21:50 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(char **argv, t_pipex *data, int argc)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	data->fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_infile < 0 || data->fd_outfile < 0)
		exit_error(2, "Error opening file", data);
	data->infile = argv[1];
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->outfile = argv[4];
	data->cmd1_args = NULL;
	data->paths = NULL;
	data->cmd_path = NULL;
	data->nr_of_cmds = argc - 3;
}

void	pipe_and_fork(t_pipex *data)
{
	if (pipe(data->pipe1_fd) == -1)
		exit_error(errno, "Pipe failed", data);
	data->pid1 = fork();
	if (data->pid1 == -1)
		exit_error(errno, "Fork failed", data);
}

void	find_cmd_path(t_pipex *data, char **envp)
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
}
