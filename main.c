#include <errno.h>
#include "shell.h"

/**
 * signal_handler - prints a new prompt upon signal
 * @sig: the signal
 *
 * Return: void
 */
void signal_handler(int sig)
{
	char *prompt = "\n$ ";

	(void) sig;
	signal(SIGINT, signal_handler);
	write(STDIN_FILENO, prompt, 3);
}

/**
 * execute - execute a command in a child process
 * @args: array of arguments
 * @name: name of the call
 * @hist: history number of the call
 *
 * Return: Error code - if an error occurs
 *         exit value of the last executed command
 */
int execute(char **args, char *name, int hist)
{
	pid_t child_pid;
	int status, flag = 0, ret;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		if (flag)
			free(command);
		perror("Error child:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (!command || (access(command, F_OK) == -1))
		{
			if (errno == EACCES)
				_exit(create_error(name, hist, args, 126));
			else
				_exit(create_error(name, hist, args, 127));
		}

		execve(command, args, NULL);
		if (errno == EACCES)
			_exit(create_error(name, hist, args, 126));
	}
	else
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}

	if (flag)
		free(command);
	return (ret);
}

/**
 * handle_args - gets and calls the execution of a command
 * @name: name of the call
 * @hist: history numbe rof the call
 *
 * Return: -2 - if EOF is read
 *         -1 - if input can't be tokenised
 *         value of the last executed command
 */
int handle_args(char *name, int *hist)
{
	int ret;
	size_t index = 0;
	ssize_t read;
	char *line = NULL, **args;
	int (*builtin)(char **argv);

	read = getline(&line, &index, stdin);
	if (read == -1)
	{
		free(line);
		return (-2);
	}

	if (read == 1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		free(line);
		return (handle_args(name, hist));
	}

	line[read - 1] = '\0';
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		ret = builtin(args + 1);
		if (ret)
			create_error(name, *hist, args, ret);
	}
	else
		ret = execute(args, name, *hist);

	(*hist)++;

	for (index = 0; args[index]; index++)
		free(args[index]);
	free(args);

	return (ret);
}

/**
 * main - launches a simple UNIX command interpreter
 * @argc: number of arguments supplied
 * @argv: array of pointers to the arguments
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	int ret = 0, hist = 1;
	char *name = argv[0];

	signal(SIGINT, signal_handler);

	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = execute(argv + 1, name, hist);
		free_env();
		return (ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret == 0)
		{
			ret = handle_args(name, &hist);
			if (ret == -2)
			{
				free_env();
				return (0);
			}
		}
		free_env();
		return (ret);
	}

	while (1)
	{
		printf("$ ");
		ret = handle_args(name, &hist);
		if (ret == -2)
		{
			printf("\n");
			free_env();
			exit(0);
		}
	}
	free_env();
	return (ret);
}
