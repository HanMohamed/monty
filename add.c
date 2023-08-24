#include "monty.h"
#include "string.h"
/**
 * add - adds the top two elements of the stack.
 * @stack: a linked list
 * @line_number: line number
 *
 */
void add(my_stack_t **stack,unsigned int line_number)
{
	int i = 0, sum;
	my_stack_t *current = *stack;
	char *error;
	char *line = "";

	while (current != NULL)
	{
		i++;
		current = current->next;
	}

	if (!current || i < 2)
	{
		sprintf(line, "%d", line_number);
		error = strcat("L", line);
		error = strcat(error, ": can't add, stack too short\n");
		write(STDERR_FILENO, error, strlen(error));
		exit(EXIT_FAILURE);
	}
	else
	{
		current = *stack;
		sum = current->n;
		sum += current->next->n;
		current->next->n = sum;
		*stack = (*stack)->next;
		(*stack)->prev = NULL;
		free(current);
	}
}
