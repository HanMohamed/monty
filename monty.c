#include "monty.h"
int value = 0;
stack_t *top = NULL;

/**
 *main - monty interpeter
 *
 * @argc: number of arguments
 *@argv: command line arguments
 *Return: 0 on success
 */
int main(int argc, char *argv[]) {
	FILE *monty_file;
	char *buffer = NULL, *error, **token = NULL;
	int line_number = 0, i = 0, op_handler = 0;
	if (argc != 2)
	{
		error = "USAGE: monty file\n";
		write(STDERR_FILENO,error, strlen(error));
		exit(EXIT_FAILURE);
	}
	monty_file = fopen(argv[1], "r");
	if (!monty_file)
	{
		error = strcat("Error: Can't open file ", argv[1]);
		error = strcat(error, "\n");
		write(STDERR_FILENO,error, strlen(error));
		exit(EXIT_FAILURE);
	}
	while(fgets(buffer, sizeof(buffer), monty_file))
	{
		line_number++;
		token[i] = strtok(buffer, " /n/t");
		if (!token[i])
		{
			free(token);
			continue;
		}
		token[++i] = strtok(NULL, " /n/t");
		op_handler = instruction_handler(token[0],token[1],  line_number);

		if (!op_handler) {
			printf("L%d: unknown instruction %s\n", line_number, token[0]);
			free(token);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
		else if (op_handler == 2)
		{
			printf("L%d: usage: push integer\n", line_number);
			free(token);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
	}
	fclose(monty_file);
	free_stack(top);
	free(token);
	return 0;
}
/**
 * instruction_handler -
 * @buffer
 * @line
 *
 * Return: 1 if succeeded or 0 if not;
 */
int instruction_handler(char *buffer, char *argument, int line)
{
	int size = 5;
	int i, fail;

	instruction_t check [] = { 
			{"push", push},
			{"pall", pall},
			{"pop", pop},
			{"pint", pint},
			{"NULL", NULL}
	};
	
	fail = 0;
	for (i = 0; i < size; i++)
	{
		if (strcmp(check[i].opcode, buffer) == 0)
		{
			if (strcmp(check[i].opcode, "push") == 0)
			{
				if (isdigit(argument))
				{
					value = atoi(argument);
				}
				else 
				{
					fail = 2;
					return (fail);
				}
			}
			fail = 1;
			check[i].func(&top, line);
			break;
		}
	}
	return (fail);
}
