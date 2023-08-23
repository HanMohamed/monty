#include "monty.h"

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
		}
	}
	printf("L%d: unknown instruction %s\n", line, buffer);
	return (fail);
}

void push()
{
	if (top == NULL)
	{

	}
}

void pall()
{
	if (top == NULL)
		return;
	stack_t *p = top;
	while(p)
	{
		printf("%d\n", p->n);
		p = p->prev;
	}
}