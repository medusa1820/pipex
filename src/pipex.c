/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/07/02 20:30:14 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;

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
	// system("leaks pipex");
	// while (1)
	// free_all(&data);
	return (0);
}
