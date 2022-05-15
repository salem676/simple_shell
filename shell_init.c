#include "shell.h"
/**
 * main - a function that runs our shell.
 * @ac: the number of inputed arguments.
 * @av: the pointer to array of inputed arguments.
 * @env: the pointer to array of enviromental variables.
 * Return: always 0.
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **command = NULL;
	size_t buf_size = 0;
	ssize_t chars_readed = 0;
	int cicles = 0;
	(void)ac;
	/*
	 * @buffer: ptr to char as null.
	 * @command: ptr to ptr to char in null.
	 * @buf_size: in zero
	 * @chars_readed: ssize_t type in zero.
	 * @cicles: in 0
	 */
	while (1)
	{
		cicles++;
		prompt();
		signal(SIGINT, handle);
		chars_readed = getline(&buffer, &buf_size, stdin);
		if (chars_readed == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			command = tokening(buffer, " \0");
			free(buffer);
			if (_strcmp(command[0], "exit") != 0)
				shell_exit(command);
			else if (_strcmp(command[0], "cd") != 0)
				change_dir(command[1]);
			else
				create_child(command, av[0], env, cicles);
		}
		fflush(stdin);
		buffer = NULL, buf_size = 0;
	}
	if (chars_readed == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
/**
 * prompt - a function that prints the prompt.
 * Description: as above.
 * Return: nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "Hell_Shell>> ", 13);
}
/**
 * handle - a function to handle Ctr + C signal.
 * @signals: the signal to handle.
 * Description: as above.
 * Return: nothing.
 */
void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\nHell_Shell>> ", 14);
}
/**
 * _EOF - a function that chaecks if buffer is EOF.
 * @buffer: the pointer to the input string.
 * Description: as above.
 * Return: nothing.
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}
/**
 * shell_exit - a function that exits the shell.
 * @command: the pointer to tokenized command.
 * Description: as above.
 * Return: nothing.
 */
void shell_exit(char **command)
{
	int sta_tus = 0;
	/*
	 * @sta_tus: int var in zero.
	 */
	if (command[1] == NULL)
	{
		free_dp(command);
		exit(EXIT_SUCCESS);
	}
	sta_tus = _atoi(command[1]);
	free_dp(command);
	exit(sta_tus);
}
