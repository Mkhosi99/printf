#include "main.h"

/**
 * is_printable - Determines if a character is printable
 * @c: Char to be assesed
 *
 * Return: 1 if c is printable, or 0 otherwise
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascii in hexa code to buffer
 * @buffer: Array of characters
 * @i: Index indicating to start appending.
 * @ascii_code: ASCII CODE.
 * Return: 3 Always
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Clarifies if a char is a digit or not
 * @c: Char to be assesed
 *
 * Return: 1 if c is a digit or 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Places a number to specified size
 * @num: Number to be placed
 * @size: Number indicating type to place
 * Return: Placed value of number
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Places a number to specified size
 * @num: Number to be placed
 * @size: Number indicating type to place
 * Return: Placed value of number
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
