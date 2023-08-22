#include "main.h"

/**
 * handle_flags - Determines active flags
 * @format: String that is formatted to print the arguments
 * @i: Takes in a parameter
 * Return: Flags
 */

int handle_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */
	int x, curr_a;
	int flags = 0;
	const char FLAGS_CHAR[] = {'_', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_a = *i + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (x = 0; FLAGS_CHAR[x] != '\0'; x++)
			if (format[curr_a] == flags_CHAR[x])
			{
				flags |= FLAGS_ARRAY[x];
				break;
			}
		if (FLAGS_CHAR[x] == 0)
			break;
	}

	*i = curr_a - 1;

	return (flags);
}
