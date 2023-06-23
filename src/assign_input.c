/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:00:46 by musenov           #+#    #+#             */
/*   Updated: 2023/06/23 17:25:16 by musenov          ###   ########.fr       */
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
	char	*cmd_path;
	int		i;
	char	*temp;

	data->cmd1_split = ft_split(data->cmd1, ' ');
	if (data->cmd1_split == NULL)
		exit_error(4, "data.cmd1 split failed");
	ft_printf("%s\n", data->cmd1_split[0]);
	ft_printf("%s\n", data->cmd1_split[1]);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	ft_printf("%s\n", envp[i]);
	ft_printf("%s\n", (envp[i] + 5));
	data->paths = ft_split((envp[i] + 5), ':');
	i = 0;
	while (data->paths[i])
		ft_printf("%s\n", data->paths[i++]);
	i = 0;
	while (data->paths[i])
	{
		temp = ft_strjoin("/", data->cmd1_split[0]);
		cmd_path = ft_strjoin(data->paths[i], temp);
		free(temp);
		if (access(cmd_path, X_OK) != -1)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	exit_error(int exit_code, char *error_msg)
{
	ft_printf("%s\n", error_msg);
	exit(exit_code);
}
