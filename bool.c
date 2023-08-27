#include "monty.h"
/**
 * is_valid_integer - checkes for a valid integer
 * @str: argument to be checked
 * Return: True for valid integer or false
 */
bool is_valid_integer(const char *str)
{
	/*check if thge string is empty*/
	if (str == NULL || *str == '\0')
	{
		return (false);
	}
	/*check for negetive signs at the beginning*/
	if (*str == '-')
		return (false);

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}
