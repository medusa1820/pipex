/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:48:43 by musenov           #+#    #+#             */
/*   Updated: 2023/06/23 17:25:46 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	char	*cmd_path;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		exit(1);
	}
	data.fd_infile = open(argv[1], O_RDONLY);
	data.fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.fd_infile < 0 || data.fd_outfile < 0)
		exit(2);
	assign_input(argv, &data);
	data.cmd_path = find_cmd_path(&data, envp);
	ft_printf("%s\n", data.cmd_path);

	return (0);
}

// char	*get_cmd_path(char *cmd, char **envp)
// {
// 	int		i;
// 	char	*path;
// 	char	**paths;

// 	i = 0;
// 	while (ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	paths = ft_split(envp[i], ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = ft_strjoin_free(paths[i], ft_strjoin("/", cmd));
// 		if (access(path, F_OK) == 0)
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	return (NULL);
// }





/*

	initialize_pipex(&pipex);
	pipex.path_splitted = get_path_and_split(envp, &pipex);
	if (pipe(pipex.pipe_fds) == -1)
		error_exit("Pipe function failed", &pipex);
	pipex.ret_pid1 = fork();
	if (pipex.ret_pid1 == -1)
		error_exit("Failed to create first child process", &pipex);
	if (pipex.ret_pid1 == 0)
		child_process_1(argv[1], argv[2], envp, &pipex);
	pipex.ret_pid2 = fork();
	if (pipex.ret_pid2 == -1)
		error_exit("Failed to create second child process", &pipex);
	if (pipex.ret_pid2 == 0)
		child_process_2(argv[4], argv[3], envp, &pipex);
	close_pipe_fds(&pipex);
	wait_and_get_exit_code(&pipex);
	free_before_terminating(&pipex);
	return (pipex.exit_code);

*/







/*

int	main(void)
{
	int		fd;
	char	*result;

	fd = open("text0.txt", O_RDONLY);
	result = get_next_line(fd);
	while (result)
	{
		ft_printf("%s", result);
		free(result);
		result = get_next_line(fd);
	}
	close(fd);
	system("leaks pipex");
	return (0);
}

*/
