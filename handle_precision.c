#include "main.h"

/**
 * handle_precision -  Determines the precision for output
 * @format: String that is formatted to print the arguments
 * @i: The arguments listed that need to be printed
 * @list: The list of the arguments
 * Return: Precision
 */
int handle_precision(const char *format, int *i, va_list list)
{
	int curr_a = *i + 1;
	int the_precision = -1;

	if (format[curr_a] != '.')
		return (the_precision);

	the_precision = 0;

	for (curr_a += 1; format[curr_a] != '\0'; curr_a++)
	{
		if (the_digit(format[curr_a]))
		{
			the_presicion *= 10;
			the_presicion += format[curr_a] - '0';
		}

		else if (format[curr_a] == '*')
		{
			curr_a++;
			the_precision = va_arg(list, int);
			break;
		}

		else
			break;
	}

	*i = curr_a - 1;

	return (the_precision);
}
