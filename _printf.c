#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - The printf function
 * @format: The format
 * Return: Printed characters
 */
int _printf(const char *format, ...)
{
	int x, output = 0, print_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[SIZE_OF_BUFF];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (x = 0; format && format[x] != '\0'; x++)
	{
		if (format[x] != '%')
		{
			buffer[buff_ind++] = format[x];
			if (buff_ind == SIZE_OF_BUFF)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[x], 1);*/
			print_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = handle_flags(format, &x);
			width = handle_width(format, &x, list);
			precision = handle_precision(format, &x, list);
			size = handle_size(format, &x);
			++x;
			output = handle_print(format, &x, list, buffer,
				flags, width, precision, size);
			if (output == -1)
				return (-1);
			print_chars += output;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (print_chars);
}

/**
 * print_buffer - Prints contents of buffer if it exist
 * @buffer: Array of characters
 * @buff_ind: Index at which to add next character, also represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
