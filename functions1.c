#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Outputs an unsigned number
 * @types: The list of arguments
 * @buffer: Buffer array thar will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies the precision
 * @size: Specifies the size
 * Return: The number of characters printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = SIZE_OF_BUFF - 2;
	unsigned long int digit = va_arg(types, unsigned long int);

	digit = convert_size_unsgnd(digit, size);

	if (digit == 0)
		buffer[x--] = '0';

	buffer[SIZE_OF_BUFF - 1] = '\0';

	while (digit > 0)
	{
		buffer[x--] = (digit % 10) + '0';
		digit /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Outputs an unsigned number in octal notation
 * @types: The list of the arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Speciifes precision
 * @size: Speciifes size
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int x = SIZE_OF_BUFF - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_num = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buffer[x--] = '0';

	buffer[SIZE_OF_BUFF - 1] = '\0';

	while (numb > 0)
	{
		buffer[x--] = (numb % 8) + '0';
		numb /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: The list of arguments
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Speciifes size
 * Return: The number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Outputs a hexadecimal number in lower or uppercase
 * @types: The list of arguments
 * @map_to: Array of values at which to map the number to
 * @buffer: Buffer array that will handle print
 * @flags: Determines any active flags
 * @flag_ch: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: The size specifier
 * @size: The size specification
 * Return: The number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int x = SIZE_OF_BUFF - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_num = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buffer[x--] = '0';

	buffer[SIZE_OF_BUFF - 1] = '\0';

	while (numb > 0)
	{
		buffer[x--] = map_to[numb % 16];
		numb /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
