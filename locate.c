#include "shell.h"

/**
 * get_location - locates a command in the PATH
 * @command: the command to locate
 *
 * Return: NULL - if an error occurs or command can't be located
 *         full pathname of the command
 */
char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;
	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);
		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);
		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}
		dirs = dirs->next;
		free(temp);
	}

	free_list(head);
	return (NULL);
}
