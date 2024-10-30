/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:17 by maustel           #+#    #+#             */
/*   Updated: 2024/10/02 15:53:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>

/*
	1)	find path -> if not in PATH, maybe path already written in temrinal?
	2)	error handling (fe "command not found")
	3)	execve
*/

int	executor(char **envp, char **args)
{
	pid_t	id;
	char	*path;

	path = get_path(args[0], envp);
	if (!path)
		return (printf("get_path failed\n"));
	id = fork();
	if (id == -1)
		return (printf("Error: fork\n"));
	else if (id == 0)
	{
		printf("Child is playing...\n"); //any code after execve in the child process wont be executed
		sleep(1);
		execve(path, args, envp);
	}
	else if (id > 0)
	{
        wait(NULL);
        printf("Child process has finished.\n");
	}
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	// char *args[] = {"ls", "-la", NULL};
	char *args[] = {"pwd", NULL};
	const char *name = "PATH";
    const char *env_p = getenv(name);
    if(env_p){
        printf("Your %s is %s\n", name, env_p);
    }
	if (executor (envp, args))
		return (1);
	(void)argc;
	(void)argv;
	return (0);
}