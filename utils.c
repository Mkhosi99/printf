#include "main.h"

/**
 * printable - Determines if a character is printable
 * @a: Character to be looked at
 *
 * Return: 1 if c is printable or zero otherwise
 */

int printable(char a)
{
	if (a >= 32 && a < 127)
		return (1);

	return (0);
}

/**
 * appends_hexa_code - Appends the ascii code in hexadecimal code to buffer
 * @buffer: The array of characters
 * @x: Index indicating to start appending
 * @ascii: The ascii code
 * Return: 3 always
 */
int appends_hexa_code(char ascii, char buffer[], int x)
{
	char go_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii < 0)
		ascii *= -1;

	buffer[x++] = '\\';
	buffer[x++] = 'x';

	buffer[x++] = go_to[ascii / 16];
	buffer[x] = go_to[ascii % 16];

	return (3);
}

/**
 * the_digit - Determines if a character is a digit
 * @a: The character to evaluate
 *
 * Return: 1 if c is a digit or zero otherwise
 */
int the_digit(char a)
{
	if (a >= '0' && a <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Places a number to specified size
 * @digit: The number to be placed
 * @size: The number informing the type to be casted
 * Return: The casted value of digit
 */
long int convert_size_number(long int digit, int size)
{
	if (size == S_LONG)
		return (digit);
	else if (size == S_SHORT)
		return ((short)digit);

	return ((int)digit);
}

/**
 * convert_size_unsgnd - Places a number to specified size
 * @digit: The number to be placed
 * @size: The number informing the type to be casted
 * Return: The casted value of digit
 */
long int convert_size_unsgnd(unsigned long int digit, int size)
{
	if (size == S_LONG)
		return (digit);
	else if (size == S_SHORT)
		return ((unsigned short)digit);

	return ((unsigned int)digit);
}
