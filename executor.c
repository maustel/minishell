/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/15 11:30:40 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	1)	find path -> if not in PATH, maybe path already written in temrinal?
	2)	error handling (fe "command not found")
	3)	execve
*/

/*
	waitpid() blocks until the child process terminates or until a signal occur
	WIFEXITED(wstatus) macro checks if the process exited normally
	WEXITwSTATUS(wstatus) extracts the exit wstatus value from the wstatus argument
*/
int	parent_function(pid_t id, char* cmd, t_exec *test)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(id, &wstatus, 0) == -1)
		return (print_error(E_PARENT, NULL, test));
	if (WIFEXITED(wstatus))	//if programm exited normally
			exit_code = WEXITSTATUS(wstatus);	//exit_code = value with which the programm exited
	else
		return (print_error(E_PARENT, NULL, test));
	if (exit_code != 0)
		return(print_error(exit_code, cmd, test));
	return (exit_code);
}

/*
	if execve fails, its because of command not found (127)
	child then exits with 127 and the parent will store the exit state
	if it doesnt fail, exit code is 0
*/
void	single_child(char *path, char **envp, t_command example, t_exec *test)
{
	if (execve(path, example.args, envp))
		{
			if (path)
				free (path);
			free_all(&example);
			exit (127);
		}
}

bool	cmd_is_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (true);
	else
		return (false);
}

/*	when binary file not exists ./"filename"--> "No such file or directory", Errorcode: 127
	when no permission for binary file--> "Permission denied", Errorcode: 126
	when command does not exist-->"command not found", errorcode: 127
*/
char	*get_check_path(char *cmd, char **envp, t_exec *test)
{
	char	*path;

	path = get_path(cmd, envp);
	if (!path)
	{
		print_error(E_PATH, NULL, test);
		return (NULL);
	}
	else if (access(path, F_OK) != 0)
	{
		if (path)
			free (path);
		if (cmd_is_path(cmd))
			print_error(E_FILENOEXIST, cmd, test);
		else
			print_error(127, cmd, test);
		return (NULL);
	}
	if (access(path, X_OK) != 0)
	{
		if (path)
			free (path);
		print_error(E_NOPERMISSION, cmd, test);
		return (NULL);
	}
	return (path);
}

int	execute_single_command(char **envp, t_command example, t_exec *test)
{
	pid_t	id;
	char	*path;

	// if (is_built_in)
	// 	ecexute_builtin();
	if (check_redirections(example, test))
		return (1);
	path = get_check_path(example.args[0], envp, test);
	if (!path)
		return (1);
	id = fork();
	if (id == -1)
		return (print_error(errno, NULL, test));
	else if (id == 0)
		single_child(path, envp, example, test);
	else if (id > 0)
		parent_function(id, example.args[0], test);
	if (path)
		free (path);
	return (test->exit_code);
}



int	executor(char **envp, t_command example, t_exec *test)
{
	//check if nbr_pipes == 0 count the amount of pipes with ft_lstsize - 1
	if (execute_single_command(envp, example, test))
		return (free_all(&example)); // freeeee
	// else
	// 	pipechain(envp, args);
	return (test->exit_code);
}

void	create_examples(t_command *ex)
{
	ex->args = NULL;
	ex->filename = NULL;
	ex->red_symbol = NULL;
	ex->args = ft_split("/bon/echo huhu", ' ');
	// ex->filename = ft_split("out", ' ');
	// ex->red_symbol = ft_split(">", ' ');
}

int main (int argc, char **argv, char **envp)
{
	// char *args[] = {"lsa", "-la", NULL};
	t_exec test;
	t_command example;
	// int	result;

	create_examples(&example);
	test.exit_code = 0;
	if (executor (envp, example, &test))
		return (test.exit_code);
	// printf ("[Exit code: %d]\n", test.exit_code);
	// printf ("[final infile: %s]\n", test.final_infile);
	// printf ("[final outfile: %s]\n", test.final_outfile);
	// printf ("[final in red: %s]\n", test.final_in_red);
	// printf ("[final out red: %s]\n", test.final_out_red);
	free_all(&example);
	return (test.exit_code);
	(void)argc;
	(void)argv;
	return (0);
}
