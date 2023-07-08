/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/07/08 16:53:31 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipex *data, int i, char **envp, char **argv)
{
	if (data->here_doc)
		data->cmd = argv[i + 3];
	else
		data->cmd = argv[i + 2];
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
