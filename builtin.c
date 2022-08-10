#include "shell.h"

/**
 * get_builtin - matches a command with the corresponding
 *               shellby buitlin function
 * @command: command to match
 *
 * Return: function pointer to the corresponding builtin function
 */
int (*get_builtin(char *command))(char **args)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "cd", shellby_cd },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strncmp(funcs[i].name, command, _strlen(funcs[i].name)) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - initiates a normal process termination for the shellby shell
 * @args: array of arguments cntaining the exit value
 *
 * Return: 2 - if the given exit value is invalid
 *         given status value
 */
int shellby_exit(char **args)
{
	int i = 0, sign = 1;
	unsigned int num = 0;

	if (args[0])
	{
		if (args[0][i] == '-')
			sign = -1;
		for (; args[0][i]; i++)
		{
			if (args[0][i] == '-')
				sign *= -1;
			if (args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (2);
		}
	}

	args -= 1;
	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
	free_env();
	exit(num * sign);
}

/**
 * shellby_cd - changes the current directory of the shell
 * @args: array of arguments
 *
 * Return: -1 - if an error occurs
 *         0 - on success
 */
int shellby_cd(char **args)
{
	char **dir_info;
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-')
			chdir(*(_getenv("OLDPWD")) + 7);
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
				&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (2);
			}
		}
	}
	else
		chdir(*(_getenv("HOME")) + 5);

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info) == -1)
		return (-1);

	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shellby_env - prints the current environment
 * @args: array of arguments
 *
 * Return: -1 - if an error occurs
 *         0 - on success
 */
int shellby_env(char **args)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void) args;
	return (0);
}

/**
 * shellby_setenv - adds or updates an environmental variable to or in the PATH
 * @args: array of arguments
 *
 * Return: -1 - if an error occurs
 *         0 - on success
 */
int shellby_setenv(char **args)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (-1);

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (-1);

	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));

	if (!new_environ)
	{
		free(new_value);
		return (-1);
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;
	return (0);
}

/**
 * shellby_unsetenv - removes an environmental variable from the PATH
 * @args: array of arguments
 *
 * Return: -1 - if error occurs
 *         0 - on success
 */
int shellby_unsetenv(char **args)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (-1);

	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (-1);

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}

	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;
	return (0);
}
