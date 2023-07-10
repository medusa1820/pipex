/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/07/10 22:02:00 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*

The while loop is used to repeatedly call waitpid until it returns -1, 
indicating that there are no more child processes to wait for.
Inside the loop, the waitpid function is called with -1 as the first argument, 
which means it waits for any child process to terminate.
The status of the terminated child process is stored in the status variable.
If the wait_pid matches the data.pid (the last child process's ID), 
it checks if the child process terminated normally using the WIFEXITED macro.
If the child process exited normally, the WEXITSTATUS macro is used to extract 
the exit status of the child process, which is stored in the exit_code variable.

*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;
	int		status;
	int		exit_code;
	pid_t	wait_pid;

	init_data(&data, argc, argv);
	i = 0;
	while (i < data.nr_of_cmds)
		pipex(&data, i++, envp, argv);
	wait_pid = 0;
	exit_code = 0;
	while (wait_pid != -1)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == data.pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
	}
	return (exit_code);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;
// 	int		i;
// 	int		status;
// 	int		exit_code;

// 	init_data(&data, argc, argv);
// 	i = 0;
// 	while (i < data.nr_of_cmds)
// 		pipex(&data, i++, envp, argv);
// 	waitpid(data.pid, &status, 0);
// 	exit_code = 0;
// 	if (WIFEXITED(status))
// 		exit_code = WEXITSTATUS(status);
// 	return (exit_code);
// }

	// system("leaks pipex");

void	init_data(t_pipex *data, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
		exit(1);
	}
	else
	{
		data->nr_of_cmds = argc - 3;
		data->here_doc = false;
	}
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
		{
			ft_putstr_fd(\
			"Usage: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" \
			... \"cmdN\" outfile\n", 2);
			exit(1);
		}
		data->here_doc = true;
		data->nr_of_cmds = argc - 4;
	}
	data->cmd = NULL;
	data->cmd_split = NULL;
	data->paths = NULL;
	data->cmd_path = NULL;
}

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
