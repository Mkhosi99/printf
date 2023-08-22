#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Outputs an unsigned number
 * @types: List of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: The width
 * @precision: Speciifies precision
 * @size: Speciifes size
 * Return: The number of character printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = (num % 10) + '0';
		num /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Outputs unsigned number in octal notation
 * @types: List of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: The width
 * @precision: Specifies precision
 * @size: Speciifies size
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Outputs unsigned number in hexadecimal notation
 * @types: List of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: The width
 * @precision: Specifies precision
 * @size: Speciifies size
 * Return: Number of characters to be printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Outputs unsigned number in upper hexadecimal notation
 * @types: List of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: The width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: Number of characters to be printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Outputs hexadecimal interger in lower or uppercase
 * @types: List of the arguments
 * @map_to: Array of values to map number
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @flag_ch: Determines active flags
 * @width: The width
 * @precision: Specifies precision
 * @size: Specifies size
 * @size: Size specification
 * Return: Number of characters to be printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
