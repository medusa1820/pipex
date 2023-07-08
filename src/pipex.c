/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/07/08 15:35:37 by musenov          ###   ########.fr       */
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
	init_data(&data, argc, argv);
	i = 0;
	while (i < data.nr_of_cmds)
	{
		main_exec(&data, i, envp, argv);
		free_all(&data);
		i++;
	}
	waitpid(data.pid, &status, 0);
	exit_code = 0;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			exit_code = WEXITSTATUS(status);
	}
	// printf("%d", exit_code);
	// system("leaks pipex");
	// while (1)
	// free_all(&data);
	return (exit_code);
}

void	init_data(t_pipex *data, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		data->here_doc = true;
		data->nr_of_cmds = argc - 4;
	}
	else
		data->nr_of_cmds = argc - 3;
	data->cmd = NULL;
	data->cmd_split = NULL;
	data->paths = NULL;
	data->cmd_path = NULL;
}

void	get_fd_infile(char **argv, t_pipex *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{	
		here_doc_open(data, argv);
		data->fd_infile = open("here_doc_file", O_RDONLY);
	}
	else
	{
		data->fd_infile = open(argv[1], O_RDONLY);
	}
	if (data->fd_infile < 0)
		exit_error(errno, "Error openning file", data);
}

void	here_doc_open(t_pipex *data, char **argv)
{
	char	*buffer;
	int		fd_here_doc;

	fd_here_doc = open("here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc < 0)
		exit_error(errno, "Error creating temporary here_doc_file", data);
	while (1)
	{
		ft_putstr_fd("here_doc>", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strlen(argv[2]) == ft_strlen(buffer) - 1 && \
		!ft_strncmp(buffer, argv[2], ft_strlen(argv[2])))
		{
			free(buffer);
			close(fd_here_doc);
			break ;
		}
		else
		{
			ft_putstr_fd(buffer, fd_here_doc);
		}
		free(buffer);
	}
	close(fd_here_doc);
}




void	get_fd_outfile(char **argv, t_pipex *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{	
		data->fd_outfile = open(argv[data->nr_of_cmds + 3], \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		data->fd_outfile = open(argv[data->nr_of_cmds + 2], \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (data->fd_outfile < 0)
		exit_error(errno, "Error openning file", data);
}
