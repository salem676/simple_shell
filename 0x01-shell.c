/**
 * File: 0x01-shell.c
 * Description: Removes print parse to test the program with different
 * commands.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>
#include "shell.h"
/**
 * @x: unused variable for convenience.
 */
#define UNUSED(x) ((void)x)

char *_strcat(char *dest, char *src);
char *_strdup(char *original);
int _strlen(char *s);
char **find_path(char **env);
char **split_line(char *line, char *delim);
char **concat_command(char **dirs_path, char *cmd);
char *read_line(void);
char *remove_char(char *line, char c);
void execute_path(char **_path);
char **make_env(char **env);

/**
 * _strcat - Appends src string to dest string. Overwrites '\0' at
 * the end of dest string.
 * @str1: Points to string where src will be copied.
 * @str2: Points to string to be copied.
 * Description: as above.
 * Return: a pointer to the resulting string dest.
 */
char *_strcat(char *str1, char *str2)
{
	int i, len1, len2;
	char *new_str;
	/*
	 * @i: counter.
	 * @len1: lenght 1, @len2: lenght 2.
	 * @new_str: ptr to nu str.
	 */
	len1 = _strlen(str1);
	len2 = _strlen(str2);
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	for (i = 0; i < len1; i++)
		new_str[i] = str1[i];
	for (i = 0; i < len2; i++)
		new_str[len1 + i] = str2[i];
	new_str[len1 + len2] = '\0';
	return (new_str);
}
/**
 * _strdup - Function that creates a mem alloc space for a string copy.
 * @original: Char array to be duplicated.
 * Description: Function that duplicates a string.
 * Return: Copy of the original string or NULL if failed.
 */
char *_strdup(char *original)
{
	char *copy;
	int i, len;
	/*
	 * @copy: pointer to char.
	 * @i: counter.
	 * @: lenght.
	 */
	if (!original)
		return (NULL);
	len = _strlen(original);
	copy = malloc((len + 1) * sizeof(char));
	for (i = 0; i <= len; i++)
		copy[i] = original[i];
	return (copy);
}
/**
 * _strlen - Function that returns the length of a string.
 * @s: Pointer to the char string.
 * Description: The standard library provides a similar function: strlen.
 * Run man strlen to learn more.
 * Return: Length of a string.
 */
int _strlen(char *s)
{
	int i = 0;
	/*
	 * @i: counter.
	 */
	while (s[i])
		i++;
	return (i);
}
/**
 * make_env - returns double pointer to char.
 * @env: pointer to pointerto char.
 * Description: constructs environment var.
 * Return: double pointer to char.
 */
char **make_env(char **env)
{
	char **newenv = NULL;
	size_t i;
	/*
	 * @newenv: pointer to pointer to char.
	 * @i: size_t counter.
	 */
	for (i = 0; env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		newenv[i] = _strdup(env[i]);
	newenv[i] = NULL;
	return (newenv);
}
/**
 * find_path - Creates a 2D array with PATH contents.
 * @env: An array of strings from the PATH environment.
 * Description: as above.
 * Return: The newly created 2D array.
 */
char **find_path(char **env)
{
	char *path_line = "PATH=";
	char *delim = ":";
	char **path;
	unsigned int i, j;
	/*
	 * @path_line: almacenates stated.
	 * @delim: almacenates :.
	 * @path: double pointer to char.
	 * What's left are counters.
	 */
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path_line[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	path = split_line(_strdup(env[i] + 5), delim);
	return (path);
}

/**
 * split_line - receives a string from the stream and splits it
 * into an arrays of tokens.
 * @line: the string to be split.
 * @delim: the delimiter character used to separate into tokens.
 * Description: as stated above .
 * Return: the array of created tokens.
 */
char **split_line(char *line, char *delim)
{
	int i = 0;
	char *token;
	char **tokens = malloc(sizeof(char *) * 100);
	/*
	 * @i: counter.
	 * @token: pointer to char.
	 * @allocated double pointer to char.
	 */
	if (tokens == NULL)
	{
		printf("Error: Failed to allocate memory.\n");
		exit(1);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 * concat_command - concatenates command given .
 * @dirs_path: double pointer, path direction.
 * @cmd: command pointer to char.
 * Description:. as above.
 * Return: double pointer to char.
 */
char **concat_command(char **dirs_path, char *cmd)
{
	int len, bufsize = 64, i = 0;
	char *cmd_cp, *err;
	char **tokens = malloc(bufsize * sizeof(char *));
	/*
	 * @len: measures lenght.
	 * @bufsize: determined.
	 * @i: counter.
	 * @cmd_cp: variable string to copy.
	 * @err: pointer to char error.
	 * @tokens: double pointer to char allocated.
	 */
	while (dirs_path[i] != NULL)
	{
		cmd_cp = cmd;
		len = _strlen(dirs_path[i]);
		if (dirs_path[i][len - 1] != '/')
			cmd_cp = _strcat("/", cmd_cp);

		cmd_cp = _strcat(dirs_path[i], cmd_cp);
		/* Handles errors by testing access function */
		if (access(cmd_cp, F_OK) == -1)
		{
			err = "\t\tFile Not Found";
		}
		else
		{
			if (access(cmd_cp, X_OK) == -1)
				err = "\t\tFile Found\t\tNot Execute Permission";
			else
				err = "\t\tFile Found\t\tExecute Permission";
		}
		tokens[i] = _strcat(cmd_cp, err);
		i++;

	}
	return (tokens);
}

/**
 * print_parse - Function that prints a 2D-pointer array.
 * @args: 2D-pointer array to be printed.
 * Description: Function used for testing.
 * Return: Void.
 */
void print_parse(char **args)
{
	int i = 0, j;
	/*
	 * Counters.
	 */
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			printf("%c", args[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
/**
 * remove_char - removes char from line.
 * @line: line given.
 * @c: char to remove.
 * Description: as above.
 * Return: pointer to char.
 */
char *remove_char(char *line, char c)
{
	char *new_line;
	int i, j, len;
	/*
	 * @new_line: pointer to char.
	 * @i,j: counters.
	 * @len: lenght.
	 */
	len = _strlen(line);
	new_line = malloc((len + 1) * sizeof(char));
	for (i = 0, j = 0; j < len; i++, j++)
	{
		if (line[i] == c)
			j++;
		new_line[i] = line[j];
	}
	new_line[i] = '\0';
	return (new_line);
}
/**
 * read_line - this functions reads a line. 
 * Description: as above.
 * Return: pointer to char.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	/*
	 * @line: ptr to char.
	 * @bufsize: size_t var buf.
	 */
	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(0);
		else
		{
			perror("End not reached");
			exit(1);
		}
	}
	line = remove_char(line, '\n');
	return (line);
}
/**
 * execute_path - executes path given.
 * @_path: path given.
 * Description: as above.
 * Return: void.
 */
void execute_path(char **_path)
{
	int i = 0, status;
	pid_t child_pid;
	char *_arg[] = {NULL};
	char *_env[] = {NULL};
	/*
	 * @i: counter.
	 * @status: status for system.
	 * @_arg: pointer to char.
	 * @_env: -.
	 */
	while (_path[i] != NULL)
	{
		printf("Aquí estoy 1!\n");
		if (access(_path[i], X_OK) != -1)
		{
			printf("Aquí estoy 2!\n");
			printf("Executing the command on: %s\n", _path[i]);
			sleep(1);
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error: Unable to create fork");
				exit(1);
			}
			if (child_pid == 0)
			{
				_arg[0] = _path[i];
				_arg[1] = NULL;
				if (execve(_path[i], _arg, _env) == -1)
					printf("%s: No such file or directory\n", _path[i]);
			}
			else
			{
				sleep(3);
				wait(&status);
				printf("\n");
				break;
			}
		}
		i++;
	}
	if (_path[i] == NULL)
		printf("Not executable file found\n");
}
/**
 * main - Runs a simple UNIX-like command interpreter.
 * @argc: The number of arguments.
 * @argv: A double pointer to the array of arguments passed to the function.
 * @env: The array of strings from the environment.
 * Description: as stated above.
 * Return: always 0.
 */
int main(int argc, char **argv, char **env)
{
	char **dum_path, **new_env;
	char *line;
	/*
	 * @dum_path: dummy path variable.
	 * @new_env: double pointer to char.
	 * @line: pointer to char.
	 */
	UNUSED(argc);
	UNUSED(argv);
	new_env = make_env(env);
	dum_path = find_path(new_env);
	while (1)
	{
		printf("===== Gets the command to concatenate =====\n");
		printf("$ ");
		line = read_line();
		printf("===== Concatenating path + command =====\n");
		dum_path = find_path(new_env);
		dum_path = concat_command(dum_path, line);
		printf("===== Full path after concatenation is:\n %s\n", dum_path[0]);
		printf("===== Executing command =====\n");
		execute_path(dum_path);
	}
}
