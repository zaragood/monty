#include "monty.h"
#include <string.h>

instruction_t instruction_set[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{NULL, NULL}
};

/**
 * is_valid_instruction - function checks if the instruction is valid
 * @instruction: pointer to the instruction
 * Return: 0 or 1
 */
int is_valid_instruction(const char *instruction)
{
	unsigned int i;

	for (i = 0; i < sizeof(instruction_set) / sizeof(instruction_set[0]); i++)
	{
		if (strcmp(instruction, instruction_set[i].opcode) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * parse_line- function that parsed the arguments
 * @command: line to be parsed
 * Return: the parsed data
 */
char **parse_line(char *command)
{
	char **parsed_data;
	int i, count = 0;
	char *token;

	parsed_data = malloc(sizeof(char *) * 3);
	if (parsed_data == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/*tokenize the command into arguments */
	token = strtok(command, " \t\n");
	if (token == NULL)
	{
		for (i = 0; i < count; i++)
		{
			free(parsed_data[i]);
		}
		free(parsed_data);
		parsed_data = NULL;
		return (NULL);
	}
	while (token && count < 2)
	{
		parsed_data[count] = _strdup(token);

		if (parsed_data[count] == NULL)
		{
			/*free previouly allocated memory*/
			for (i = 0; i < count; i++)
			{
				free(parsed_data[i]);
			}
			free(parsed_data);
			parsed_data = NULL;
			return (NULL);
		}
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
	int number, i;
	stack_t *new_node;

	if (!data || !data[1])
	{
		fprintf(stderr, "L%u: usage: push interger\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_integer(data[1]))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(stack);
		for (i = 0; data[i] != NULL; i++)
		{
			free(data[i]);
		}
		free(data);
		exit(EXIT_FAILURE);
	}

	number = atoi(data[1]);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "ERROR: malloc failed\n");
		free_stack(stack);
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

/**
 * pint - function that prints the value at the top of the stack
 * @stack: double pointer to the stack
 * @line_number: index of each element in the stack
 */
void pint(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
