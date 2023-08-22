#include "main.h"

/** PRINT CHAR **/

/**
 * print_char - Prints character
 * @types: The list of the arguments
 * @buffer: The buffer array that will handle print
 * @flags: Determines active flags if any
 * @width: Indicates the width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: The number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}
/************************* PRINT STRING *************************/
/**
 * print_string - Outputs a string
 * @types: The list a of arguments
 * @buffer: The buffer array that will handle print
 * @flags: Determines active flags if any
 * @width: Indicates the width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: The number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, x;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Outputs a percent sign
 * @types: The list of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Detrmines active flags
 * @width: Indicates width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: The number of characetrs printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print interger
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: The number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = SIZE_OF_BUFF - 2;
	int negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int digit;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[SIZE_OF_BUFF - 1] = '\0';
	digit = (unsigned long int)n;

	if (n < 0)
	{
		digit = (unsigned long int)((-1) * n);
		negative = 1;
	}

	while (digit > 0)
	{
		buffer[x--] = (digit % 10) + '0';
		digit /= 10;
	}

	x++;

	return (write_number(negative, x, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Outputs unsigned number
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, j, z, sum;
	unsigned int a[32];
	int add;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = x / j;
	for (z = 1; z < 32; z++)
	{
		j /= 2;
		a[z] = (x / j) % 2;
	}
	for (z = 0, sum = 0, add = 0; z < 32; z++)
	{
		sum += a[z];
		if (sum || z == 31)
		{
			char z = '0' + a[z];

			write(1, &z, 1);
			add++;
		}
	}
	return (add);
}
