#include "monty.h"
/**
 *push - function to add a node to the stack
 *
 *@stack: linked list
 *@line_number: number of lines
 *
 */
void push(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *new = malloc(sizeof(stack_t));

	if (new == NULL)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (*stack == NULL)
	{
		new->n = value;
		new->next = NULL;
		new->prev = NULL;
		*stack = new;
	}
	else 
	{
		new->n = value;
		new->next = *stack;
		new->prev = NULL;
		(*stack)->prev = new;
		*stack = new;
	}
}
/**
 *pall - funciton to print alinked list content
 *
 *@stack: linked list
 *@line_number: number of lines
 *
 */
void pall(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *current = *stack;

	if (current == NULL)
		return;

	while (current->next != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
/**
 *pint - function to print the top of alinked list
 *
 *@stack: linked list
 *@line_number: number of lines
 *
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		printf("L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%d\n", (*stack)->n);
	}
}
/**
 *pop - function that removes the top element of stack
 *
 *@stack: linked list
 *@line_number: number of lines
 *
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	if (current == NULL)
	{
		printf("L%d: can't pop an empty stack", line_number);
		exit(EXIT_FAILURE);
	}
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(current);
}
/**
 * free_stack - frees a dlistint_t list
 *
 * @stack: head of the list
 * Return: no return
 */
void free_stack(stack_t *stack)
{
	stack_t *current;

	while (stack != NULL)
	{
		current = stack;
		stack = stack->next;
		free(current);
	}
}

