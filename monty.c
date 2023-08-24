#include "monty.h"

/**main - monty interpeter
 *
 * @argc: number of arguments
 *@argv: command line arguments
 *Return: 0 on success
 */
int main(int argc, char *argv[]) {
	FILE *monty;
	char *buffer = NULL, *error, **token = malloc(2 * sizeof(char **));
	int line_number = 0, op_handler = 0;
	stack_t *stack = NULL;
	size_t n = 0;

	if (argc != 2)
	{
		error = "USAGE: monty file\n";
		write(STDERR_FILENO,error, strlen(error));
		exit(EXIT_FAILURE);
	}
	monty = fopen(argv[1], "r");	
	if (monty == NULL)
	{
		error = strcat("Error: Can't open file ", argv[1]);
		error = strcat(error, "\n");
		write(STDERR_FILENO,error, strlen(error));
		exit(EXIT_FAILURE);
	}
	while(getline(&buffer, &n, monty) != -1)
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

		if (!op_handler) {
			printf("L%d: unknown instruction %s\n", line_number, token[0]);
			free(token);
			fclose(monty);
			exit(EXIT_FAILURE);
		}
		else if (op_handler == 2)
		{
			printf("L%d: usage: push integer\n", line_number);
			free(token);
			fclose(monty);
			exit(EXIT_FAILURE);
		}
	}
	fclose(monty);
	free(token);
	free(buffer);
	free_stack(stack);
	return 0;
}
/**
 * instruction_handler -
 * @buffer
 * @line
 *
 * Return: 1 if succeeded or 0 if not;
 */
int instruction_handler(char *buffer, char *argument, int line, stack_t **stack)
{
	int i;
	

	instruction_t check [] = { 
			{"push", push},
			{"pall", pall},
			{"pop", pop},
			{"pint", pint},
	};
	
	for (i = 0; i < 4; i++)
	{
		if (strcmp(check[i].opcode, buffer) == 0)
		{
			if (strcmp(check[i].opcode, "push") == 0)
			{
				if (_isdigit(argument))
					value = atoi(argument);
				else
					return (2);
			}
			check[i].func(stack, line);
			return (1);
		}
	}
	return (0);
}
/**
 * _isdigit - Checks for a digit 0 through 9
 * Return: 0 or 1
 * @c: Variable
 **/
int _isdigit(char *c)
{
	char *aux = c;

	if (c == NULL)
		return (0);
	if (*aux == '-')
		aux++;

	for (; *aux != '\0'; aux++)
	{
		if ((*aux < '0' || *aux > '9'))
		{
			return (0);
		}
	}
	return (1);
}
