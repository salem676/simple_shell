#include "shell.h"
/**
 * free_dp - a function that frees all the memory allocated for command.
 * @command: the pointer to allocated memory to free.
 * Description: as above.
 * Return: nothing.
 */
void free_dp(char **command)
{
	size_t i = 0;
	/*
	 * @i: in zero.
	 */
	if (command == NULL)
		return;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	if (command[i] == NULL)
		free(command[i]);
	free(command);
}
/**
 * free_exit - a function that frees all the memory allocated and exit.
 * @command: the pointer to allocated command memory to free.
 * Description: as above.
 * Return: nothing.
 */
void free_exit(char **command)
{
	size_t i = 0;
	/*
	 * @i: in zero
	 */
	if (command == NULL)
		return;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	if (command[i] == NULL)
		free(command[i]);
	free(command);
	exit(EXIT_FAILURE);
}
