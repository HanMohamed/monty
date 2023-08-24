#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} my_stack_t;

extern int value;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @func: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*func)(my_stack_t **stack, unsigned int line_number);
} instruction_t;

int _isdigit(char *c);
int instruction_handler(char *buffer, char *argument,
						int line, my_stack_t **stack);
void free_stack(my_stack_t *stack);
void push(my_stack_t **stack, unsigned int line_number);
void pall(my_stack_t **stack, unsigned int line_number);
void pop(my_stack_t **stack, unsigned int line_number);
void pint(my_stack_t **stack, unsigned int line_number);
void add(my_stack_t **stack, unsigned int line_number);
void nop(my_stack_t **stack, unsigned int line_number);
void swap(my_stack_t **stack, unsigned int line_number);
#endif
