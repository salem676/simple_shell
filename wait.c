/*
 * File: wait.c
 * Author: salem676
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - fork & wait example.
 * Description: forks and waits.
 * Return: 0.
 */
int main(void)
{
	pid_t child_pid;
	int status;
	/*
	 * @child_pid: process var pid_t type.
	 * @status: integer tells status.
	 */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		printf("Wait for me, wait for me\n");
		sleep(3);
	}
	else
	{
		wait(&status);
		printf("Oh, it's all better now\n");
	}
	return (0);
}
