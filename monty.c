#include "monty.h"

/**
 * main - monty interpreter
 *
 * @argc: number of arguments
 * @argv: command line arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	FILE *monty;
	char *buffer = NULL, *error, **token = malloc(2 * sizeof(char **));
	int line_number = 0, op_handler = 0;
	my_stack_t *stack = NULL;
	size_t n = 0;

	if (argc != 2)
	{
		error = "USAGE: monty file\n";
		write(STDERR_FILENO, error, strlen(error));
		exit(EXIT_FAILURE);
	}
	monty = fopen(argv[1], "r");
	if (monty == NULL)
	{
		error = strcat("Error: Can't open file ", argv[1]);
		error = strcat(error, "\n");
		write(STDERR_FILENO, error, strlen(error));
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &n, monty) != -1)
	{
		line_number++;
		token[0] = strtok(buffer, " \n\t");
		if (!token[0])
		{
			free(token);
			continue;
		}
		token[1] = strtok(NULL, " \n\t");
		op_handler = instruction_handler(token[0], token[1], line_number, &stack);

		if (!op_handler)
			printf("L%d: unknown instruction %s\n", line_number, token[0]);
		else if (op_handler == 2)
			printf("L%d: usage: push integer\n", line_number);
		else
			continue;

		free(token);
		fclose(monty);
		exit(EXIT_FAILURE);
	}
	fclose(monty);
	free(token);
	free(buffer);
	free_stack(stack);
	return (0);
}
