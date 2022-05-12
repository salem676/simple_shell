/*
 * File: exec_prog.c
 * Author: salem676
 */
#include <stdio.h>
#include <unistd.h>
/**
 * main - exec. example.
 * Description: executes example.
 * Return: 0.
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	/*
	 * @argv: pretedermined string.
	 */
	printf("Before execve\n");
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	printf("After execve\n");
	return (0);
}
