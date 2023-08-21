#include "main.h"
/**
 * write_pointer - write a memory address
 * @index: index
 * @buffer: buffer array to handle print
 * @flag: Calculates active flags.
 * @width: get width.
 * @l: length
 * @padd: padding char
 * @extra_c: extra char
 * @padd_start: index
 * Return: Number of chars printed
 *
 */
int write_pointer(char buffer[], int index, int l, int width, int flag,
		char padd, char extra_c, int padd_start)
{
	int i;

	if (width > l)
	{
		for (i = 3; i < width - l + 3; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flag & F_MINUS && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], l) + write(1, &buffer[3], i - 3));
		}
		else if (!(flag & F_MINUS) && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], l));
		}
		else if (!(flag & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
			write(1, &buffer[index], l - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

/**
 * write_num - print a string
 * @index: index
 * @buffer: buffer array
 * @flag: calculates active flags.
 * @width: get width.
 * @prec: precision specifier
 * @l: length
 * @padd: padding char
 * @extra_c: extra char
 * Return: Number of chars printed
 *
 */
int write_num(int index, char buffer[], int flag, int width,
int prec, int l, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padd = ' ';
	if (prec > 0 && prec < l)
		padd = ' ';
	while (prec > l)
		buffer[--index] = '0', l++;
	if (extra_c != 0)
		l++;
	if (width > l)
	{
		for (i = 1; i < width - l + 1; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flag & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], l) + write(1, &buffer[1], i - 1));
		}
		else if (!(flag & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], l));
		}
		else if (!(flag & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
			write(1, &buffer[index], l - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], l));
}

/**
 * handle_write_char -prints a string
 * @c: char types
 * @buffer: buffer array
 * @flag: Calculates active flags.
 * @width: get width.
 * @prec: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */
int handle_write_char(char c, char buffer[], int flag, int width,
int prec, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(size);

	if (flag & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;
		if (flag & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/*  WRITE NUMBER */
/**
 * write_number - print a string
 * @is_negative: lista if arguments
 * @index: char types
 * @buffer: buffer array
 * @flag: Calculates active flags.
 * @width: get width.
 * @prec: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */
int write_number(int is_negative, int index, char buffer[], int flag,
int width, int prec, int size)
{
	int l = BUFF_SIZE - index - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flag & F_PLUS)
		extra_ch = '+';
	else if (flag & F_SPACE)
		extra_ch = ' ';

	return (write_num(index, buffer, flag, width, prec,
		l, padd, extra_ch));
}

/**
 * write_unsgnd_number - writes an unsigned number
 * @is_negative: if num is negative
 * @index: char types
 * @buffer: buffer array
 * @flag: calculates active flags.
 * @width: get width.
 * @prec: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 *
 */
int write_unsgnd_number(int is_negative, int index, char buffer[],
int flag, int width, int prec, int size)
{
	int l = BUFF_SIZE - index - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (prec > 0 && prec < l)
		padd = ' ';

	while (prec > l)
	{
		buffer[--index] = '0';
		l++;
	}
	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padd = '0';

	if (width > l)
	{
		for (i = 0; i < width - l; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flag & F_MINUS)
		{
			return (write(1, &buffer[index], l) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], l));
		}
	}
	return (write(1, &buffer[index], l));
}
