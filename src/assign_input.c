/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/06/25 20:50:28 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	assign_input(char **argv, t_pipex *data)
{
	data->infile = argv[1];
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->outfile = argv[4];
}

char	*find_cmd_path(t_pipex *data, char **envp)
{
	char	*cmd_path_func;
	int		i;
	char	*temp;

	data->cmd1_args = ft_split(data->cmd1, ' ');
	if (data->cmd1_args == NULL)
		exit_error(4, "data.cmd1 split failed", data);
	// ft_printf("%s\n", data->cmd1_args[0]);
	// ft_printf("%s\n", data->cmd1_args[1]);
	// ft_printf("%s\n", data->cmd1_args[2]);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	// ft_printf("%s\n", envp[i]);
	// ft_printf("%s\n", (envp[i] + 5));
	data->paths = ft_split((envp[i] + 5), ':');
	if (data->paths == NULL)
		exit_error(5, "envp[i] split failed", data);
	// i = 0;
	// while (data->paths[i])
	// 	ft_printf("%s\n", data->paths[i++]);
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd1_args[0]);
		cmd_path_func = ft_strjoin(data->paths[i], temp);
		free(temp);
		if (access(cmd_path_func, X_OK) != -1)
			return (cmd_path_func);
		free(cmd_path_func);
		i++;
	}
	return (NULL);
}
