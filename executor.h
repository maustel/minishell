/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:59:19 by maustel           #+#    #+#             */
/*   Updated: 2024/10/24 17:19:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"

# ifndef BASE_PATH
#  define BASE_PATH "tmp/heredoc_temp"
# endif

typedef enum e_custom_err
{
	E_CUSTOM_ARGC = 107,
	E_PATH,
	E_PARENT,
	E_FILENOEXIST,
	E_NOPERMISSION,
	E_ISDIRECTORY,
	E_SYNTAXERROR = 258
}			t_custom_err;

typedef enum e_print_err
{
	NOTPRINT,
	PRINT
}			t_print_err;

//t_list:
//void *content --> t_command *example
//t_list *next

typedef struct s_command
{
	char	**args;
	char	**filename;
	char	**red_symbol;
	int		id;
	char	*path;				//to free
	char	*final_infile;
	char	*final_outfile;
	char	*final_in_red;
	char	*final_out_red;
	char	*heredoc_file_path;	//to free
} t_command;

typedef struct	s_exec
{
	int		exit_code;
	int		nbr_pipes;
	// char	*final_infile;
	// char	*final_outfile;
	// char	*final_in_red;
	// char	*final_out_red;
}					t_exec;

typedef struct s_shell
{
	t_list		*table;	//content->t_command row
	t_exec		*exec;
	char		**envp;
}					t_shell;

char	*get_path(char *cmd, char **envp);
void	free_paths(char **split_paths, char **append);
int		print_error(int err_no, char *str, t_exec *test);
int		check_files(t_list *table, t_exec *test);
int		exec_redirections(t_command *row, t_exec *test);
void	free_double(char **to_free);
int		free_row(t_command *example);
int		execute_pipechain(char **envp, t_list *table, t_exec *test);
int		handle_stuff(char **envp, t_list *table, t_exec *test);
int		get_check_path(t_list *table, char **envp, t_exec *test);
int		free_table(t_list *table);
int		handle_heredoc(t_list *table, t_exec *test);
int		redirect_input(t_command row,t_exec *test, int *fd);
int		redirect_output(t_command row, t_exec *test, int *fd);

#endif
