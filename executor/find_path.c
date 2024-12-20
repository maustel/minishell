/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:24:16 by maustel           #+#    #+#             */
/*   Updated: 2024/11/29 12:06:55 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*-------------------------------------------------------------
Allocate memory for double-array
---------------------------------------------------------------*/
char	**allocate_append_array(char **split_paths)
{
	int		j;
	char	**append;

	j = 0;
	while (split_paths[j] != NULL)
		j++;
	append = malloc(sizeof(char *) * (j + 1));
	return (append);
}

/*-------------------------------------------------------------
Concatenate path and command
---------------------------------------------------------------*/
char	*concatenate_path_cmd(char *path, char *cmd)
{
	char	*slash;
	char	*full_path;

	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
	full_path = ft_strjoin(slash, cmd);
	free(slash);
	return (full_path);
}

/*-------------------------------------------------------------
Add slash '/' to each possible path in split_paths**:
concatinate path + '/' + command --> /usr/bin + '/' + ls = /usr/bin/ls
---------------------------------------------------------------*/
char	**add_slash_cmd(char **split_paths, char *cmd)
{
	int		i;
	char	**append;

	i = 0;
	append = allocate_append_array(split_paths);
	if (!append)
		return (NULL);
	while (split_paths[i] != NULL)
	{
		append[i] = concatenate_path_cmd(split_paths[i], cmd);
		if (!append[i])
			return (NULL);
		i++;
	}
	append[i] = NULL;
	return (append);
}

/*-------------------------------------------------------------
check if cmd exists and is executable
X_OK for execute/search permission
F_OK existence test
0 sucessful
---------------------------------------------------------------*/
char	*check_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if ((access(cmd[i], F_OK) == 0) && (access(cmd[i], X_OK) == 0))
			return (cmd[i]);
		i++;
	}
	return (NULL);
}

/*-------------------------------------------------------------
Add path to command
get all env paths where command could be
get first '/' and split into small paths between the ':'
/usr/local/bin:/usr/bin: --> /usr/local/bin  --  /usr/bin
---------------------------------------------------------------*/
char	*get_path(char *cmd, char **envp)
{
	char	*big_path;
	char	**split_paths;
	char	**append;
	char	*move;
	char	*path;

	if (cmd[0] == '.' && cmd[1] == '/')
		return (ft_strdup(cmd));
	append = NULL;
	if (envp[0] == NULL)
		return (NULL);
	big_path = search_env(envp, "PATH");
	if (big_path == NULL)
		return (ft_strdup(cmd));
	move = ft_strchr(big_path, '/');
	if (move == NULL)
		return (free(big_path), ft_strdup(cmd));
	split_paths = ft_split(move, ':');
	if (!split_paths)
		return (NULL);
	append = add_slash_cmd(split_paths, cmd);
	path = ft_strdup(check_cmd(append));
	if (path == NULL)
		return (free_paths(split_paths, append, big_path), ft_strdup(cmd));
	return (free_paths(split_paths, append, big_path), path);
}
