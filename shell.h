#ifndef _SHELL_H_
#define _SHELL_H_

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

/**
 * struct list_s - struct defining a linke dlist
 * @dir: directory path
 * @next: pointer to a struct list_s
 */
typedef struct list_s
{
	struct list_s *next;
	char *dir;
} list_t;

/**
 * struct builtin_s - struct defining buitlin commands
 * @name: name of the builtin command
 * @f: function pointer to the command function
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv);
} builtin_t;

char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
char *fill_path_dir(char *path);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
void free_env(void);
char **_copyenv(void);
char **_getenv(const char *name);
int num_len(int num);
char *_itoa(int num);
int create_error(char *name, int hist, char **args, int err);
int (*get_builtin(char *command))(char **args);
int shellby_exit(char **args);
int shellby_cd(char **args);
int shellby_env(char **args);
int shellby_setenv(char **args);
int shellby_unsetenv(char **args);
int create_error(char *name, int hist, char **args, int err);
char *error_env(char *name, int hist, char **args);
char *error_2_exit(char *name, int hist, char **args);
char *error_2_cd(char *name, int hist, char **args);
char *error_126(char *name, int hist, char **args);
char *error_127(char *name, int hist, char **args);

#endif /* _SHELL_H_ */
