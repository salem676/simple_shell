/*
 * File: get_ppid.c
 * Author: salem676
 */
#include <stdio.h>
#include <unistd.h>
/**
 * main - PID main.
 * Description: main tests pid and prints child/parent. 
 * Return: 0.
 */
int main(void)
{
	pid_t my_pid;
	/*
	 * @my_pid: pid_t structure instance.
	 */
	my_pid = getpid();
	printf("child %u\n", my_pid);
	my_pid = getppid();
	printf("parent %u\n", my_pid);
	return (0);
}
