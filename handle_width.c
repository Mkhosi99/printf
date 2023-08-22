#include "main.h"

/**
 * handle_width - Determines the width to be printed
 * @format: String that is formatted to print the arguments
 * @i: The list of arguments that must be printed
 * @list: The list of the arguments
 * Return: width
 */
int handle_width(const char *format, int *i, va_list list)
{
	int curr_a;
	int the_width = 0;

	for (curr_i = *i + 1; format[curr_a] != '\0'; curr_a++)
	{
		if (the_digit(format[curr_a]))
		{
			the_width *= 10;
			the_width += format[curr_a] - '0';
		}

		else if (format[curr_a] == '*')
		{
			curr_a++;
			the_width = va_arg(list, int);
			break;
		}

		else
			break;
	}

	*i = curr_a - 1;

	return (the_width);
}
