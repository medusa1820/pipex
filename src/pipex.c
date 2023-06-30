/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/06/30 20:45:54 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;

	if (argc < 5)
		exit_error(1, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", NULL);
	init_data(argv, &data, argc);
	i = 0;
	while (i < argc - 3)
	{
		main_exec(&data, i, envp, argv, argc);
		i++;
	}



	/*
	pipe_and_fork_1(&data);
	find_cmd_path_1(&data, envp);
	if (data.pid0 == 0)
	{
		dup2(data.fd_infile, STDIN_FILENO);
		close(data.fd_infile);
		close(data.fd_outfile);
		dup2(data.pipe0_fd[1], STDOUT_FILENO);
		close(data.pipe0_fd[0]);
		close(data.pipe0_fd[1]);
		if (execve(data.cmd_path, data.cmd1_args, envp) == -1)
			exit_error(126, "Couldn't execute execve()", &data);
	}
	close(data.fd_infile);
	pipe_and_fork_2(&data);
	find_cmd_path_2(&data, envp);
	if (data.pid1 == 0)
	{
		// pipe0
		dup2(data.pipe0_fd[0], STDIN_FILENO);
		close(data.pipe0_fd[0]);
		close(data.pipe0_fd[1]);
		// pipe1
		// dup2(data.pipe1_fd[1], STDOUT_FILENO);
		dup2(data.fd_outfile, STDOUT_FILENO);
		close(data.fd_outfile);
		close(data.pipe1_fd[0]);
		close(data.pipe1_fd[1]);
		if (execve(data.cmd_path, data.cmd2_args, envp) == -1)
			exit_error(126, "Couldn't execute execve()", &data);
	}
	close(data.pipe0_fd[0]);
	close(data.pipe0_fd[1]);
	close(data.pipe1_fd[0]);
	close(data.pipe1_fd[1]);
	close(data.fd_outfile);
	*/



	// system("leaks pipex");
	// while (1)
	free_all(&data);
	return (0);
}
