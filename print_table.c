
#include "minishell.h"

size_t  nbr_of(char **str)
{
    size_t i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}

void  print_contents(char **str)
{
    size_t i;

    i = 0;
    while (str[i] != NULL)
    {
        printf("\033[35m[%s]\033[0m", str[i]);
        i++;
    }
}

void    print_struct_table(t_list *table)
{
    t_command   *current_cmd;

    current_cmd = (t_command *)table->content;
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of args:         [%zu]\n", nbr_of(current_cmd->args));
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of red symbols:  [%zu]\n\033[0m", nbr_of(current_cmd->red_symbol));
    printf("\033[32m|\033[0m");
    printf("\033[33m Nbr of filenames:    [%zu]\n", nbr_of(current_cmd->filename));
    printf("\033[32m|\033[0m");

    printf("\033[32m\n|\033[0m");
    printf("\033[35m ARGS:         ");
    print_contents(current_cmd->args);
    printf("\033[32m\n|\033[0m");
    printf("\033[35m REDIRECTIONS: \033[0m");
    print_contents(current_cmd->red_symbol);
    printf("\033[32m\n|\033[0m");
    printf("\033[35m FILENAMES:    ");
    print_contents(current_cmd->filename);
    printf("\033[32m\n|\033[0m");
}

void    print_table(t_shell *shell)
{
    t_list *tmp;
    size_t  line;

    if (shell->syntax_error == true)
        return ;
    tmp = shell->table;
    line = 1;
    while (tmp != NULL)
    {
        printf("\033[32m|------------------------------------|\n");
        printf("|            [line: %zu]               |\n", line);
        printf("\033[32m|------------------------------------|\n");
        print_struct_table(tmp);
        printf("\033\n[32m|-------------end-of-line------------|\033[0m\n\n");

        tmp = tmp->next;
        line++;
    }
}