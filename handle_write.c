#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Outputs string
 * @c: character types
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indictaes width
 * @precision: Speciifies precision
 * @size: Specifies size
 * Return: The number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int x = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[x++] = c;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFF_SIZE - x - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - x - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Outputs string
 * @is_negative: List of the arguments
 * @ind: character types
 * @buffer: Buffer array that will handle print
 * @flags: Determines active flags
 * @width: Indicates width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: The number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write number using buffer
 * @ind: Index indicating when the number starts on the buffer
 * @buffer: The buffer
 * @flags: The flags
 * @width: The width
 * @prec: Specifies precision
 * @length: Number of lenght
 * @padd: Pading character
 * @extra_c: Extra character
 * Return: Number of printed characters
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int x, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buffer[x] = padd;
		buffer[x] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], x - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], x - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], x - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned interger
 * @is_negative: Number indicating if interger is negative
 * @ind: Index indicating when the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Specifies flags
 * @width: Speciifes width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: Number of written characters
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, x = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (x = 0; x < width - length; x++)
			buffer[x] = padd;

		buffer[x] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], x));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], x) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Writes memory address
 * @buffer: Arrays of characters
 * @ind: Index indicating when number starts in the buffer
 * @length: Length of the interger
 * @width: Width
 * @flags: Flags
 * @padd: Char that represents the padding
 * @extra_c: Char that represents extra char
 * @padd_start: Index indicating when padding should start
 * Return: Number of written characters
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int x;

	if (width > length)
	{
		for (x = 3; x < width - length + 3; x++)
			buffer[x] = padd;
		buffer[x] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], x - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], x - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], x - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
