// file: my_fscanf.c
#include "my_fscanf.h"
#include <stdarg.h>
#include <ctype.h>
void my_fscanf(FILE *fp, const char *format, ...) {
	va_list list;
	va_start(list, format);
	while (*format) {
		if (*format == '%') {
			int c;
			format++;
			switch (*format) {
			case 'd':
			{
				while (isspace(c = getc(fp))) {}

				int* addr = va_arg(list, int*);
				*addr = 0;
				while (isdigit(c)) {
					*addr = *addr * 10 + c - '0';
					c = getc(fp);
				}
				
				while (isspace(c = getc(fp))) {}

				ungetc(c, fp);
				break;
			}
			case 'c':
				{
					while (isspace(c = getc(fp))) {}

					char* addr = va_arg(list, char*);
					*addr = c;
					break;
				}
			}
		}
		else
			format++;
	}
	va_end(list);
}
