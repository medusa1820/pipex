/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/07/07 22:30:15 by musenov          ###   ########.fr       */
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

// void	init_data(char **argv, t_pipex *data, int argc)
void	init_data(t_pipex *data, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
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
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{	
		here_doc_open(data, argv);
		data->fd_infile = open("here_doc_file", O_RDONLY);
	}
	else
	{
		ft_printf("value of argv[1]: %s\n", argv[1]);
		ft_printf("length of argv[1]: %d\n", ft_strlen(argv[1]));
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
		// ft_printf("%d\n", 1);
		ft_putstr_fd("here_doc>", STDOUT_FILENO);
		// ft_printf("%d\n", 2);
		buffer = get_next_line(STDIN_FILENO);
		// ft_printf("%d\n", 3);
		// if (!ft_strncmp(argv[2], buffer, ft_strlen(argv[2]) + 1))
		if (ft_strlen(argv[2]) + 1 == ft_strlen(buffer)
		&& !ft_strncmp(buffer, argv[2], ft_strlen(argv[2] + 1)))
		{
			// ft_printf("%d\n", 4);
			free(buffer);
			close(fd_here_doc);
			break ;
		}
		else
		{
			// ft_printf("%d\n", 5);
			ft_putstr_fd(buffer, fd_here_doc);
		}
		// ft_printf("%d\n", 6);
		free(buffer);
		// ft_printf("%d\n", 7);
	}
	// ft_printf("%d\n", 8);
	close(fd_here_doc);
	// ft_printf("%d\n", 9);
}

// void	here_doc_open(t_pipex *data, char **argv)
// {
// 	char	*buffer;
// 	int		fd_here_doc;

// 	fd_here_doc = open("here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd_here_doc < 0)
// 		exit_error(errno, "Error creating temporary here_doc_file", data);
// 	buffer = get_next_line(STDIN_FILENO);
// 	while (buffer)
// 	{
// 		ft_putstr_fd("here_doc>", STDOUT_FILENO);
// 		// if (ft_strncmp(argv[2], buffer, ft_strlen(argv[2])))
// 		if (ft_strlen(argv[2]) + 1 == ft_strlen(buffer)
// 		&& !ft_strncmp(buffer, argv[2], ft_strlen(argv[2] + 1)))
// 		{
// 			// ft_printf("argv[2]: %s\n", argv[2]);
// 			// ft_printf("length of argv[2]: %d\n", ft_strlen(argv[2]));
// 			// ft_printf("buffer: %s\n", buffer);
// 			// ft_printf("length of buffer: %d\n", ft_strlen(buffer));
// 			free(buffer);
// 			close(fd_here_doc);
// 			break ;
// 		}
// 		else
// 			ft_putstr_fd(buffer, fd_here_doc);
// 		free(buffer);
// 		buffer = get_next_line(STDIN_FILENO);
// 		// ft_putstr_fd("here_doc>", STDOUT_FILENO);
// 	}
// 	close(fd_here_doc);
// }



void	get_fd_outfile(char **argv, t_pipex *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
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

