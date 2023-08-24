#include "monty.h"
/**
 * free_stack - function that frees the whole stack before exiting
 * @stack: pointer to the stack
 */
void free_stack(stack_t **stack)
{
	stack_t *temp = *stack, *next;

	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*stack = NULL;
}

