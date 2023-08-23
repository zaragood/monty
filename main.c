#include "monty.h"
/**
 *
 *
 */
char **data;
char buffer[LIMIT]; /*Buffer for reading lines*/

int main(int argc, char *argv[])
{
	size_t length, i;
	unsigned int line_number = 0;
	stack_t *stack;
	FILE *file_ptr;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	
	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	/* initializing an empty stack */
	stack = NULL;
	
	/*read lines from the file*/
	while (fgets(buffer,  sizeof(buffer), file_ptr))
	{
		line_number++;

		length = strlen(buffer);
		if (length > 0 && buffer[length - 1] == '\n')
		{
			buffer[length - 1] = '\0';
		}

		/*parse the line into opcode and arguments*/

		data = parse_line(buffer);

		/*call the opcode function on the according to the data parsed*/
		if (data != NULL && data[0] != NULL)
		{
			if(strcmp(data[0], "push") == 0)
			{
				push(&stack, line_number);
			}
			else if (strcmp(data[0], "pall") == 0)
			{
				pall(&stack, line_number);
			}
		}
		for (i = 0; data[i] != NULL; i++)
		{
			free(data[i]);
		}
		free(data);
	}
	/*free the entire stack when the program exit*/
	free_stack(&stack);

	fclose(file_ptr);
	return (EXIT_SUCCESS);
}
