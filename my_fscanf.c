#include "my_fscanf.h"
#include <ctype.h>
#include <stdarg.h>
void my_fscanf(FILE *fp, const char *format, ...) {
	va_list list;
	va_start(list, format);
	while (*format) {
		if (*format == '%') {
			int aa=0;
			format++;
			switch (*format) {
			case 'd':
			{
				while (isspace(aa = getc(fp))) {}
				int* kk = va_arg(list, int*);
				*kk = 0;
				while (isdigit(aa)) {
					*kk = *kk * 10 + aa - '0';
					aa = getc(fp);
				}
				while (isspace(aa = getc(fp))) {}
				format++;
				ungetc(aa, fp);
				break;
			}
			case 'c':
			{
				while (isspace(aa = getc(fp))) {}
				char* kkk = va_arg(list, char*);
				*kkk = aa;
				format++;
				break;
			}
			case 's':
			{
				char* kkkk = va_arg(list, char*);
				int cc = 1;
				while (isspace(aa = getc(fp))) {}
				kkkk[0] = aa;
				while (!isspace(aa = getc(fp))) {
					kkkk[cc] = aa;
					cc++;
				}
				kkkk[cc] = 0; //add null char
				format++;
				ungetc(aa, fp);
				break;
			}
			case 'f':
			{
				double* kf = va_arg(list, double*);
				double sosu = 0.1;
				while (isspace(aa = getc(fp))) {}
				*kf = 0;
				while (isdigit(aa)) {
					*kf = *kf * 10 + aa - '0';
					aa = getc(fp);
				}
				if (aa == '.') {
					aa = getc(fp);
					while (isdigit(aa)) {
						*kf = *kf + (aa - '0') * sosu;
						sosu = sosu * 0.1;
						aa = getc(fp);
					}
				}
				format++;
				ungetc(aa, fp);
				break;
			}
			}
		}
		else {
			int aa = getc(fp);
			if (*format == aa)
				format++;
		}
	}
	va_end(list);
}