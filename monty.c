#include "monty.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	instruction_t *instruction;
	FILE *monty_file;
	char *buffer, *error;
	int line_number = 0;
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
		//TODO: parse string
		instruction = malloc(sizeof(instruction_t));
		if (!instruction)
		{
			error = "Error: malloc failed\n";
			write(STDERR_FILENO,error, strlen(error));
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}

		instruction->opcode = buffer;
		line_number++;
		//TODO: buffer ??!!
		if (!buffer)
		{
			printf("L%d: unknown instruction %s\n", line_number, instruction->opcode);
			free(instruction);
			fclose(monty_file);
			exit(EXIT_FAILURE);
		}
	}
	fclose(monty_file);
	return 0;
}
