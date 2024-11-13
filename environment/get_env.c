#include "../executor.h"

int	copy_env(char **env, t_shell *shell)
{
	size_t i;
	char **new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = safe_malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = safe_ft_strdup(env[i]);
		if (!new_env)
			return (clear_all(new_env), -1);
		i++;
	}
	new_env[i] = NULL;
	shell->env = duplicate_double_ptr(new_env);
	if (!shell->env)
		return (clear_all(new_env), -1);
	clear_all(new_env);
	// shell->env = new_env; // probably have to duplicate here
	return (0);
}
