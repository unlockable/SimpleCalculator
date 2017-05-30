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

				format++;
				ungetc(c, fp);
				break;
			}
			case 'c':
			{
				while (isspace(c = getc(fp))) {}

				char* addr = va_arg(list, char*);
				*addr = c;
				format++;
				break;
			}
			case 's':
			{
				char* addr = va_arg(list, char*);
				int cnt = 1;
				while (isspace(c = getc(fp))) {}

				addr[0] = c;

				while (!isspace(c = getc(fp))) {
					addr[cnt] = c;
					cnt++;
				}
				addr[cnt] = 0; //add null char
				format++;
				ungetc(c, fp);
				break;
			}
			case 'f':
			{
				double* addr = va_arg(list, double*);
				double decimalFraction = 0.1;

				while (isspace(c = getc(fp))) {}
				*addr = 0;
				while (isdigit(c)) {
					*addr = *addr * 10 + c - '0';
					c = getc(fp);
				}

				if (c == '.') {
					c = getc(fp);
					while (isdigit(c)) {
						*addr = *addr + (c - '0') * decimalFraction;
						decimalFraction *= 0.1;
						c = getc(fp);
					}
				}
				format++;
				ungetc(c, fp);
				break;
			}

			}

		}
		else {
			int c = getc(fp);
			if (*format == c)
				format++;
		}
	}
	va_end(list);
}
