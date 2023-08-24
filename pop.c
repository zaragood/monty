#include "monty.h"
/**
 * pop - The opcode pop removes the top element of the stack
 * @stack: ponter to the stack
 * @line_number: index of each element in the stack
 */
void pop(stack_t **stack, unsigned int line_number)
{
        stack_t *temp;
        (void)line_number;

        if (*stack == NULL)
        {
                fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
                exit(EXIT_FAILURE);
        }

        temp = *stack;
        *stack = (*stack)->next;

        if (*stack != NULL)
        {
                (*stack)->prev = NULL;
        }
        free(temp);
}
