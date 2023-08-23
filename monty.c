#include "monty.h"
/**
 * parse_line- function that parsed the arguments
 * @command: line to be parsed
 * Return: the parsed data
 */
char **parse_line(char *command)
{
	char **parsed_data;
	int count = 0;
	char *token;

	parsed_data = malloc(sizeof(char *) * 2);
	if (parsed_data == NULL)
	{
		return (NULL);
	}

	/*tokenize the command into arguments */
	token = strtok(command, " \t\n");
	if (token == NULL)
	{
		free(parsed_data);
		parsed_data = NULL;
		return (NULL);
	}
	while (token && count < 2)
	{
		parsed_data[count] = token;
		token = strtok(NULL, " \t\n");
		count++;
	}
	parsed_data[count] = NULL;
	return (parsed_data);
}

/**
 * push - function that adds an element to an empty stack
 * @stack: double pointer to the empty stack
 * @line_number: index of each element in the stack
 */
void push(stack_t **stack, unsigned int line_number)
{
	int number;
	stack_t *new_node;

	if (!data || !data[1])
	{
		fprintf(stderr, "L%u: usage: push interger\n", line_number);
		exit(EXIT_FAILURE);
	}

	number = atoi(data[1]);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "ERROR: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = number;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}
	*stack = new_node;
}

/**
 * pall - function that prints all values stored int the stack
 * @stack: double poinetre to the stack
 * @line_number: index of each element in the stack
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	(void)line_number;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}
