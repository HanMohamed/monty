#include "monty.h"
/**
 *main - monty interpeter
 *
 * @argc: number of arguments
 *@argv: command line arguments
 *Return: 0 on success
 */
int main(int argc, char *argv[]) {
	FILE *monty_file;
	char *buffer, *error, **token = NULL;
	int line_number = 0, i = 0, op_handler;
	stack_monty = NULL;
	top = NULL;
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
		op_handler = instruction_handler(token[0], line_number);

		if (!op_handler)
		{
			dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n", line_number, token[0]);
			free(token);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
	}
	fclose(monty_file);
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
int instruction_handler(char *buffer, int line)
{
	int instruction_size = 6;
	int i, fail;

	fail = 0;
	instruction_t check_instruction[] = {
			{"push", push},
			{"pall", pall},
			{"pop", pop},
			{"pint", pint},
			{"swap", swap},
			{"add", add}
	};

	for (i = 0; i < instruction_size; i++)
	{
		if (strcmp(check_instruction[i].opcode, buffer) == 0)
		{
			fail = 1;
			check_instruction[i].func(stack_monty, line);
			break;
		}
	}
	return (fail);
}
