#include "monty.h"

/**
 * add - adds the top two elements of the stack.
 * @stack: a linked list
 * @line_number: line number
 *
 */
void add(my_stack_t **stack, unsigned int line_number)
{
	int i = 0, sum;
	my_stack_t *current = *stack;
	char error[1024];

	while (current != NULL)
	{
		i++;
		current = current->next;
	}

	current = *stack;
	if (!current || i < 2)
	{
		sprintf(error, "L%d: can't add, stack too short\n", line_number);
		write(STDERR_FILENO, error, strlen(error));
		exit(EXIT_FAILURE);
	}
	else
	{
		sum = current->n;
		sum += current->next->n;
		current->next->n = sum;
		*stack = (*stack)->next;
		if (*stack)
			(*stack)->prev = NULL;
		free(current);
	}
}

/**
 * nop - does not do anything.
 *
 * @stack: a linked list
 * @line_number: line number
 */
void nop(my_stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	(void) stack;
}

/**
 * swap - swaps the top two elements of the stack
 *
 * @stack: a linked list
 * @line_number: line number
 */
void swap(my_stack_t **stack, unsigned int line_number)
{
	int i = 0, temp;
	my_stack_t *current = *stack;
	char error[1024];

	while (current != NULL)
	{
		i++;
		current = current->next;
	}

	current = *stack;
	if (!current || i < 2)
	{
		sprintf(error, "L%d: can't swap, stack too short\n", line_number);
		write(STDERR_FILENO, error, strlen(error));
		exit(EXIT_FAILURE);
	}
	else
	{
		temp = current->n;
		current->n = current->next->n;
		current->next->n = temp;
	}
}

/**
 * instruction_handler - handel instructions
 * @buffer: buffer
 * @argument: argument
 * @line: line
 * @stack: stack
 *
 * Return: 1 if succeeded or 0 if not;
 */
int instruction_handler(char *buffer, char *argument,
						int line, my_stack_t **stack)
{
	int i;
	int instructions = 7;

	instruction_t check[] = {
			{"push", push},
			{"pall", pall},
			{"pop", pop},
			{"pint", pint},
			{"add", add},
			{"nop", nop},
			{"swap", swap}
	};

	for (i = 0; i < instructions; i++)
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
			return (0);
	}
	return (1);
}
