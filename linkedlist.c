#include "shell.h"

/**
 * add_node_end - adds a node tat the end of a list_t linked list
 * @head: pointer to the head of the list_t list
 * @dir: directory path for the new node to hold
 *
 * Return: NULL - if an error occurs
 *         pointer to the new node
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * fill_path_dir - copies path
 * @path: colon-separated list of directories
 *
 * Return: copy of path
 */
char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}

	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);

	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
			_strncat(path_copy, &path[i], 1);
	}

	return (path_copy);
}

/**
 * free_list - frees a list_t linked list from memory
 * @head: head of the list_t list
 *
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

/**
 * get_path_dir - converts a colon-sepated list of directories into a
 *                list_t linked list
 * @path: colon-sepated list of directories
 *
 * Return: pointer to the linked list
 */
list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);

	if (!path_copy)
		return (NULL);

	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);
	return (head);
}
