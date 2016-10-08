#include <libdev.h>

void		print_trace(void) {
	void	*array[BACKTRACE_SIZE];
	char	**strings;
	size_t	size, i;

	size = backtrace(array, BACKTRACE_SIZE);
	strings = backtrace_symbols(array, size);
	for (i = 0; i < size; i++) {
		write(2, "\033[0;37m> \033[0m", 13);
		write(2, strings[i], strlen(strings[i]));
		write(2, "\n", 1);
	}
}

void		error(char *str, ...) {
	va_list		ap;

	write(2, "\033[0;31m> \033[0m", 13);
	va_start(ap, str);
	vfprintf(stderr, str, ap);
	if (str[strlen(str) - 1] != '\n')
		fprintf(stderr, "\n");
	fprintf(stderr, "\033[0;31m> Program must stop: Backtrace:\033[0m\n");
	print_trace();
	_exit(1);
}

void		info(char *str, ...) {
	va_list		ap;

	write(1, "\033[0;34m> \033[0m", 13);
	va_start(ap, str);
	vprintf(str, ap);
}

void		warning(char *str, ...) {
	va_list		ap;

	write(2, "\033[0;31m> \033[0m", 13);
	va_start(ap, str);
	vfprintf(stderr, str, ap);
}
