/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:58:33 by musenov           #+#    #+#             */
/*   Updated: 2023/07/08 17:17:59 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_fd_infile(char **argv, t_pipex *data)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
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

/*

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

*/

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