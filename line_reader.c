/*
 * File: line_reader.c
 * Author: salem676
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * main - prototype line reader.
 * Description: as above.
 * Return: 0.
 */
int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;
	/*
	 * @buffer: allocated buffer, with 1024.
	 * @len: size_t var with 1024.
	 */
	while (1)
	{
		printf("$ ");
		getline(&buffer, &len, stdin);
		printf("%s", buffer);
	}
	return (0);
}
