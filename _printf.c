#include "main.h"

void clean(va_list ar, buffer_t *output);
int run_printf(const char *format, va_list ar, buffer_t *output);
int _printf(const char *format, ...);

/**
 * clean - Peforms cleanup operationsr _printf.
 * @ar: A va_list of arguments provided to _printf.
 * @output: A buffer_t struct.
 */
void clean(va_list ar, buffer_t *output)
{
	va_end(ar);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @ar: A va_list of arguments.
 *
 *
 * Return: The number of characters stored to output.
 */

int run_printf(const char *format, va_list ar, buffer_t *output)
{
	int i, wid, prec, ret = 0;
	char tmp;
	unsigned char flag, len;

/**
  * int - brief Used in conjunction with a variadic function.
  * to output formatted text.
  * @f: pointer variabe.
  * va_list: A variable argument list of type 'va_list'.
  * buffer_t: A pointer to a buffer_t struct to store the output.
  * unsigned_char: An unsigned char representing a format specifier.
  *
  *
  * Return:return An unsigned integer representing the number.
  */

	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flag = handle_flags(format + i + 1, &tmp);
			wid = handle_width(ar, format + i + tmp + 1, &tmp);
			prec = handle_precision(ar, format + i + tmp + 1,
					&tmp);
			len = handle_length(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret += f(ar, output, flag, wid, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	clean(ar, output);
	return (ret);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list ar;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(ar, format);

	ret = run_printf(format, ar, output);

	return (ret);
}
