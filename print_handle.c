#include "main.h"

/**
 * handle_print - An argument is printed based on its type
 * @fmt: String that is formatted to print arguments
 * @list: The list of arguments that must be printed
 * @ind: ind
 * @buffer: The buffer array that handles print
 * @flags: Determines any active flags present
 * @width: gets the width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: 1 or 2;
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int x, unknown_len = 0, printed_char = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (x = 0; fmt_types[x].fmt != '\0'; x++)
		if (fmt[*ind] == fmt_types[x].fmt)
			return (fmt_types[x].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[x].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);

		else if (width)
		{
			--(*ind);

			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}

		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}

	return (printed_char);
}
