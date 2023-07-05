/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/07/05 19:41:13 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	// char	*temp;
	// char	*to_free;

	if (ft_strnstr(data->cmd, "/", ft_strlen(data->cmd)))
	{
		prepare_cmd_split(data);
		prepare_paths(data, envp);
		// prepare_cmd_path_0(data);
		prepare_cmd_path_slash(data);
		// prepare_cmd_path(data);
	}
	// else if (ft_strnstr(data->cmd, "$(which", ft_strlen(data->cmd)))
	// {
	// 	data->cmd_split = ft_split(data->cmd, ')');
	// 	if (data->cmd_split == NULL)
	// 		exit_error(errno, "data.cmd split failed", data);
	// 	temp = ft_strjoin(data->cmd_split[0], ")");
	// 	to_free = data->cmd_split[0];
	// 	data->cmd_split[0] = temp;
	// 	free(to_free);
	// 	data->cmd_path = data->cmd_split[0];
	// }
	else
	{
		prepare_cmd_split(data);
		prepare_paths(data, envp);
		prepare_cmd_path(data);
	}
}

void	find_cmd_path_1(t_pipex *data, char **envp)
{
	char	*temp;
	char	*to_free;

	if (ft_strnstr(data->cmd, "$(which", ft_strlen(data->cmd)))
	{
		data->cmd_split = ft_split(data->cmd, ')');
		if (data->cmd_split == NULL)
			exit_error(errno, "data.cmd split failed", data);
		temp = ft_strjoin(data->cmd_split[0], ")");
		to_free = data->cmd_split[0];
		data->cmd_split[0] = temp;
		free(to_free);
		data->cmd_path = data->cmd_split[0];
	}
	else
	{
		prepare_cmd_split(data);
		prepare_paths(data, envp);
		prepare_cmd_path_0(data);
	}
}

void	find_cmd_path_2(t_pipex *data, char **envp)
{
	prepare_cmd_split(data);
	prepare_paths(data, envp);
	if (ft_strnstr(data->cmd_split[0], "/", ft_strlen(data->cmd_split[0])))
		prepare_cmd_path_slash(data);
	else
		prepare_cmd_path(data);
}

void	prepare_cmd_split(t_pipex *data)
{
	data->cmd_split = ft_split(data->cmd, ' ');
	if (data->cmd_split == NULL)
		exit_error(4, "data.cmd split failed", data);
}

void	prepare_paths(t_pipex *data, char **envp)
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=/", 6) == 0)
		i++;
	data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
}

void	prepare_cmd_path(t_pipex *data)
{
	char	*cmd_path_func;
	char	*temp;
	int		i;

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
}

void	prepare_cmd_path_0(t_pipex *data)
{
	char	*cmd_path_func;
	char	*temp;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		if (ft_strnstr(data->cmd_split[0], "/", ft_strlen(data->cmd_split[0])))
			prepare_cmd_path_slash(data);
		else
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
	}
	if (data->paths[i] == NULL)
		exit_error(127, "Command not found", data);
}

void	prepare_cmd_path_slash(t_pipex *data)
{
	// int		i;

	// i = 0;
	// while (data->paths[i])
	// {
	// 	if (access(data->cmd_split[0], X_OK) != -1)
	// 	{
	// 		data->cmd_path = data->cmd_split[0];
	// 		break ;
	// 	}
	// 	i++;
	// }
	// if (data->paths[i] == NULL)
	// 	exit_error(127, "Command not found", data);

	if (access(data->cmd_split[0], X_OK) != -1)
		data->cmd_path = data->cmd_split[0];
	else
		exit_error(127, "Command not found", data);
}
