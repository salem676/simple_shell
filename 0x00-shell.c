#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/**
 * _strcat - appends src string to dest string. Overwrites \0 end of dest.
 *		Then adds \0.
 *
 * @dest: points to the string where string will be copied
 * @src: points to the string to be copied
 *
 * Return: a pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int i, len = 0;

	while (dest[len] != '\0')
		len++;

	for (i = 0; src[i]; i++)
		dest[len++] = src[i];

	return (dest);
}

/**
 * split_line - receives a string from the stream and splits it
 * into an arrays of tokens.
 *
 * @line: the string to be split.
 * @delim: the delimiter character used to separate into tokens.
 *
 * Return: the array of created tokens.
 */
char **split_line(char *line, char *delim)
{
	int i = 0;
	char *token;
	/* Each element of the array of tokens @tokenArr */
	char **tokenArr = malloc(sizeof(char *) * 100);

	if (tokenArr == NULL)
	{
		printf("Error: Failed to allocate memory.\n");
		exit(1);
	}

	token = strtok(line, delim);
	while (token != NULL)
	{
		tokenArr[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	tokenArr[i] = NULL;

	return (tokenArr);
}


/**
 * main - Runs a simple UNIX-like command interpreter.
 *
 * @argc: The number of arguments.
 * @argv: A double pointer to the array of arguments passed to the function.
 * @env: The array of strings from the environment.
 *
 * Return: always 0.
 */
int main(int __attribute__((unused))argc, char __attribute__((unused))**argv, char const __attribute__((unused))**env)
{
	char *line = NULL;
	size_t bufsize = 0;
	char **commds = malloc(sizeof(char *) * 100);
	int i = 0;

	while (1)
	{
		printf("$ ");
		getline(&line, &bufsize, stdin);
		commds = split_line(line, " ");
		if (!commds)
		{
			printf("Error: \n");
			exit(1);
		}

		while (commds[i])
		{
			if (commds[i + 1] == NULL)
			{
				printf("%s", commds[i]);
				break;
			}
			printf("%s\n", commds[i]);
			i++;
		}
		commds[i] = NULL;
	}

	return (0);
}
