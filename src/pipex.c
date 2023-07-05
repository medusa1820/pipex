/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/07/05 14:00:58 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;
	int		status;
	int		exit_code;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
		exit(1);
	}
		// exit_error(1, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", &data);
	init_data(argv, &data, argc);
	i = 0;
	while (i < argc - 3)
	{
		main_exec(&data, i, envp, argv);
		free_all(&data);
		i++;
	}
	waitpid(data.pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	// printf("%d", exit_code);
	// system("leaks pipex");
	// while (1)
	// free_all(&data);
	return (exit_code);
}

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
