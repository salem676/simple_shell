#include "shell.h"
/**
 * tokening - a function that split and create a full string command.
 * @s: the delimiter for strtok.
 * @buffer: the pointer to input string.
 * Description: as above.
 * Return: a string with full command.
 */
char **tokening(char *buffer, const char *s)
{
	char *token = NULL, **commands = NULL;
	size_t bufsize = 0;
	int i = 0;
	/*
	 * @token: ptr to char in null.
	 * @commands: ptr to ptr to char in null.
	 * @bufsize: in zero.
	 * @i: counter to zero.
	 */
	if (buffer == NULL)
		return (NULL);
	bufsize = _strlen(buffer);
	commands = malloc((bufsize + 1) * sizeof(char *));
	if (commands == NULL)
	{
		perror("Unable to allocate buffer");
		free(buffer);
		free_dp(commands);
		exit(EXIT_FAILURE);
	}
	token = strtok(buffer, s);
	while (token != NULL)
	{
		commands[i] = malloc(_strlen(token) + 1);
		if (commands[i] == NULL)
		{
			perror("Unable to allocate buffer");
			free_dp(commands);
			return (NULL);
		}
		_strcpy(commands[i], token);
		token = strtok(NULL, s);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
