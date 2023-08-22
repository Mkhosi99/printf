#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define SIZE_OF_BUFF 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 *struct fmt - Struct op
 * @fmt: Indicates the format
 * @fn: The function related
 */

struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - struct op
 * @fmt: The indicated format
 * @fm_t: The function related
 */
typedef struct fmt fm_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
		va_list, char buffer[], int flags int width, int precision, int size);

/************** FUNCTIONS *******************/

/* The functions that print chars and strings */
int printf_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int width, int size);

/* Functions that print numbers */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer,
		int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],
		char buffer[], char flag_ch, int flags, int width, int precision, int size);

/* Function that prints a character that can't be printed */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Function that prints the memory address */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Functions that handle other specifiers */
int handle_flags(const char *format, int *i);
int handle_width(const char *format, int *i, va_list list);
int handle_precision(const char *format, int *i, va_list list);
int handle_size(const char *format, int *i);

/* Function that prints string in reverse */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Function to output a string in rot 13 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Width handler */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[]'
		int flags, int width, int precision, int size);
int write_num(int ind, char buffer[],
		int flags, int width, int precision, int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start);
int write_unsigned(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size);

/*************** UTILS ***************/
int printable(char);
int appends_hexa_code(char, char[], int);
int the_digit(char);
long int convert_size_unsgnd(unsigned long int digit, int size);
long int convert_size_number(long int digit, int size);

#endif
