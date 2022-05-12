/*
 * File: print_args.c
 * Author: salem676
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * main - prototype of print args.
 * @ac: argument 1.
 * @av: argument 2.
 * Return: 0.
 */
int main(int ac, char **av)
{
	int i = 0;
	/*
	 * @i: counter.
	 */
	while (av[i])
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("\n");
	return (0);
}
