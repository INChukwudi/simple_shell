#include "shell.h"

/**
 * num_len - counts the digit length of a number
 * @num: number to get its digit length
 *
 * Return: digit length
 */
int num_len(int num)
{
	int len = 1;

	while (num > 9)
	{
		len++;
		num /= 10;
	}

	return (len);
}

/**
 * _itoa - converts an interger to a string
 * @num: integer to be converted
 *
 * Return: converted string
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);


	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';
	len--;
	while (len >= 0)
	{
		buffer[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}

	return (buffer);
}

/**
 * create_error - writes an error message to standard error (stderr)
 * @name: name of the call throwing the error
 * @hist: history number of the call
 * @args: array of arguments
 * @err: error value
 *
 * Return: error value
 */
int create_error(char *name, int hist, char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = error_env(name, hist, args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = error_2_exit(name, hist, args);
			else
				error = error_2_cd(name, hist, args);
			break;
		case 126:
			error = error_126(name, hist, args);
			break;
		case 127:
			error = error_127(name, hist, args);
			break;
	}
	write(STDERR_FILENO, error, _strlen(error));
	if (error)
		free(error);

	return (err);
}
