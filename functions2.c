#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Outputs the value of pointer variable
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The number of characters printed
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_ch = 0, padd = ' ';
	int index = SIZE_OF_BUFF - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char go_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[SIZE_OF_BUFF - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[index--] = go_to[num_addrs % 16];
		num_addrs /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_ch = '+', len++;
	else if (flags & F_SPACE)
		extra_ch = ' ', len++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, index, len,
		width, flags, padd, extra_ch, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Outputs ascii code in hexa of non printable characters
 * @types: Thw list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0, balance = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[x] != '\0')
	{
		if (is_printable(str[x]))
			buffer[x + balance] = str[x];
		else
			balance += appends_hexa_code(str[x], buffer, x + balance);

		x++;
	}

	buffer[x + balance] = '\0';

	return (write(1, buffer, x + balance));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Outputs revers of string
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int x, add = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char a = str[x];

		write(1, &a, 1);
		add++;
	}
	return (add);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Output a string in rot13.
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *str;
	unsigned int a, b;
	int add = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				c = out[b];
				write(1, &c, 1);
				add++;
				break;
			}
		}
		if (!in[b])
		{
			c = str[a];
			write(1, &c, 1);
			add++;
		}
	}
	return (add);
}
