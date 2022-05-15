#include "shell.h"
/**
 * execute - a function that executes a command.
 * @command: the pointer to tokenized command.
 * @name: the name of the shell.
 * @env: the pointer to the enviromental variables.
 * @cicles: number of executed cicles.
 * Description: as above.
 * Return: nothing.
 */
void execute(char **command, char *name, char **env, int cicles)
{
	char **pathways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i = 0;
	/*
	 * @pathways: ptr to ptr to null.
	 * @full_path: ptr to null.
	 * @i: counter
	 */
	if (_strcmp(command[0], "env") != 0)
		print_env(env);
	if (stat(command[0], &st) == 0)
	{
		if (execve(command[0], command, env) < 0)
		{
			perror(name);
			free_exit(command);
		}
	}
	else
	{
		pathways = _getPATH(env);
		while (pathways[i])
		{
			full_path = _strcat(pathways[i], command[0]);
			i++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, command, env) < 0)
				{
					perror(name);
					free_dp(pathways);
					free_exit(command);
				}
				return;
			}
		}
		msgerror(name, cicles, command);
		free_dp(pathways);
	}
}
/**
 * print_env - a function that prints all enviromental variables.
 * @env: the pointer to enviromental variables.
 * Description: as above.
 * Return: nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;
	/*
	 * @i: counter.
	 * @len: length
	 */
	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
/**
 * _getPATH - a function to gets the full value from.
 * enviromental variable PATH.
 * @env: the pointer to enviromental variables.
 * Description: as above.
 * Return: all tokenized pathways for commands.
 */
char **_getPATH(char **env)
{
	char *pathvalue = NULL, **pathways = NULL;
	unsigned int i = 0;
	/*
	 * @pathvalue: ptr to char in null.
	 * @pathways: ptr to ptr to char in null.
	 * @i: counter.
	 */
	pathvalue = strtok(env[i], "=");
	while (env[i])
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			pathways = tokening(pathvalue, ":");
			return (pathways);
		}
		i++;
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}
/**
 * msgerror - a function that prints message not found.
 * @name: the name of the shell.
 * @cicles: number of cicles.
 * @command: the pointer to tokenized command.
 * Description: as above.
 * Return: nothing.
 */
void msgerror(char *name, int cicles, char **command)
{
	char c;
	/*
	 * @c: var for char.
	 */
	c = cicles + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &c, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command[0], _strlen(command[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
