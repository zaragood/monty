#include "monty.h"
/**
 *
 *
 */
char **data;
char buffer[LIMIT]; /*Buffer for reading lines*/
char instruction[100];

int main(int argc, char *argv[])
{
	size_t length;
	unsigned int line_number = 0, i, j;
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
		if (strlen(buffer) == 0)
		{
			continue;
		}

		/*parse the line into opcode and arguments*/

		data = parse_line(buffer);
		for (i = 0; data[i] != NULL; i++) {
    			printf("data[%d]: %s\n", i, data[i]);
		}


		/*call the opcode function on the according to the data parsed*/
		if (data != NULL && data[0] != NULL)
		{
			/*Extract the instruction from data[0]*/
			strcpy(instruction, data[0]);
			i = 0;

			if (is_valid_instruction(instruction))
			{
				while (instruction_set[i].opcode != NULL)
				{
					if(strcmp(data[0], instruction_set[i].opcode) == 0)
					{
						instruction_set[i].f(&stack, line_number);
						break;
					}
					i++;
				}
				if (instruction_set[i].opcode == NULL)
				{
					fprintf(stderr, "L%u: unknown instruction %s\n", line_number, data[0]);
					free_stack(&stack);
					fclose(file_ptr);
					for (j = 0; data[j] != NULL; j++)
                			{
                        			free(data[j]);
                			}
                			free(data);
				}
			}
			else
			{
				fprintf(stderr, "Error: Invalid instruction - %s\n", data[0]);
				free_stack(&stack);
				fclose(file_ptr);
				for (j = 0; data[j] != NULL; j++)
				{
					free(data[j]);
				}
				free(data);
				exit(EXIT_FAILURE);
			}
		}
		for (j = 0; data[j] != NULL; j++)
		{
			free(data[j]);
		}
		free(data);
	}
	/*free the entire stack when the program exit*/
	free_stack(&stack);

	fclose(file_ptr);
	return (EXIT_SUCCESS);
}
