/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:50:18 by maustel           #+#    #+#             */
/*   Updated: 2024/10/03 16:32:06 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_double(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free (to_free[i]);
		i++;
	}
	if (to_free)
		free (to_free);
}

void	free_paths(char **split_paths, char **append)
{
	if (split_paths)
		free_double (split_paths);
	if (append)
		free_double(append);
}
