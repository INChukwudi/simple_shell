#include "shell.h"

/**
 * error_env - creates an error for environment errors
 * @name: command name
 * @hist: history number of the command
 * @args: array of arguments passed to the command
 *
 * Return: the error string
 */
char *error_env(char *name, int hist, char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": ");
	_strcat(error, "Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_exit - creates an error message for shellby_exit errors
 * @name: command name
 * @hist: history number of the command
 * @args: array of arguments passed to the command
 *
 * Return: error string
 */
char *error_2_exit(char *name, int hist, char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0])
		+ _strlen(args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": ");
	_strcat(error, "Illegal Number");
	_strcat(error, ": ");
	_strcat(error, args[1]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - creates an error message for shellby_cd errors
 * @name: command name
 * @hist: history number of the command
 * @args: array of arguments passed to the command
 *
 * Return: the error string
 */
char *error_2_cd(char *name, int hist, char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0])
		+ _strlen(args[1]) + 18;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": ");
	_strcat(error, "can't cd to ");
	_strcat(error, args[1]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_126 - creates an error message for permission denied failure
 * @name: command name
 * @hist: history number
 * @args: array of arguments passsed to the command
 *
 * Return: error string
 */
char *error_126(char *name, int hist, char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));

	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, ": ");
	_strcat(error, "Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - creates an error message for command not found failures
 * @name: the command name
 * @hist: history number of the command
 * @args: array of arguemnts passed to the command
 *
 * Return: error string
 */
char *error_127(char *name, int hist, char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": ");
	_strcat(error, "not found\n");

	free(hist_str);
	return (error);
}
