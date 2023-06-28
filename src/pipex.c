/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/06/28 21:28:01 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
		exit_error(1, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", NULL);
	init_data(argv, &data, argc);
	pipe_and_fork(&data);
	find_cmd_path(&data, envp);
	
	
	// if (data.pid1 == 0)
	// {
	// 	dup2(data.fd_infile, STDIN_FILENO);
	// 	close(data.fd_infile);
	// 	dup2(data.pipe1_fd[1], STDOUT_FILENO);
	// 	close(data.pipe1_fd[1]);
	// 	close(data.pipe1_fd[0]);
	// 	if (execve(data.cmd_path, data.cmd1_args, envp) == -1)
	// 		exit_error(126, "Couldn't execute execve()", &data);
	// }


	
	if (data.pid1 == 0)
	{
		if (execve(data.cmd_path, data.cmd1_args, envp) == -1)
			exit_error(126, "Couldn't execute execve()", &data);
	}
	else
	{
		wait(NULL);
		printf("This line will not be executed.\n");
	}
	// system("leaks pipex");
	// while (1)
	free_all(&data);
	return (0);
}

