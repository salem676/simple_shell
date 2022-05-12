/*
 * File: split_str_toarray.c
 * Author: salem676
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * main - prototype split string to array.
 * Description: as above.
 * Return: 0.
 */
int main(void)
{
	char *buffer = malloc(1024);
	size_t len = 1024;
	char *token;
	/*
	 * @buffer: ptr allocated 1024.
	 * @len: size_t var with 1024.
	 * @token: ptr to char.
	 */
	while (1)
	{
		printf("$ ");
		getline(&buffer, &len, stdin);
		printf("buffer getline: %s", buffer);
	}
	token = strtok(buffer, " ");
	while (token)
	{
		printf("buffer strtok: %s\n", token);
		token = strtok(NULL, " ");
	}
	return (0);
}
