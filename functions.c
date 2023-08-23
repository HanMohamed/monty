#include "monty.h"

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
