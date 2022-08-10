#include "shell.h"

/**
 * _copyenv - creates a copy of the environment
 *
 * Return: NULL - if copy fails
 *         pointer to the copy of the environment
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);
		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}

	new_environ[index] = NULL;
	return (new_environ);
}

/**
 * free_env - fress the environment copy
 *
 * Return: void
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - gets an environmental variable from the PATH
 * @name: name of the environmental variable to get
 *
 * Return: NULL - if the environmental variable does not exist
 *         pointer to the environmental variable
 */
char **_getenv(const char *name)
{
	int index, len;

	len = _strlen(name);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(name, environ[index], len) == 0)
			return (&environ[index]);
	}
	return (NULL);
}
