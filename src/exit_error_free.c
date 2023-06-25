/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:34:26 by musenov           #+#    #+#             */
/*   Updated: 2023/06/25 21:44:17 by musenov          ###   ########.fr       */
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
	exit(exit_code);
}
