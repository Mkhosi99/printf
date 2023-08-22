#include "main.h"

/**
 * handle_size - Determines the size to cast unto the argument
 * @format: String that is formatted to print the arguments
 * @i: The list of arguments that must be printed
 * Return: Precision
 */

int handle_size(const char *format, int *i)
{
	int curr_a = *i + 1;
	int the_size = 0;

	if (format[curr_a] == 'l')
		the_size = S_LONG;

	else if (format[curr_a] == 'h')
		the_size = S_SHORT;

	if (the_size == 0)
		*i = curr_a - 1;

	else
		*i = curr_a;

	return (the_size);
}
