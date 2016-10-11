#include <libdev.h>

static void	title(char *s) {
	u_char			len = 80;
	int				i;

	len -= strlen(s);
	for (i = 0; i < len / 2; i++, write(1, "=", 1));
	write(1, " ", 1);
	write(1, s, strlen(s));
	write(1, " ", 1);
	for (; i < len; i++, write(1, "=", 1));
	write(1, "\n", 1);
}

void		register_test(char *group, char *(*fn_test)(void), char *name) {
	t_list		*tests = singleton_lists(TESTS_LIST, 0x0);
	t_test		*ptr;

	ptr = malloc(sizeof(t_test));
	L_ASSERT(ptr);
	ptr->group = malloc(strlen(group));
	ptr->name = malloc(strlen(name));
	L_ASSERT(ptr->group && ptr->name);
	strcpy(ptr->group, group);
	strcpy(ptr->name, name);
	ptr->fn_test = fn_test;
	list_add(tests, ptr, sizeof(t_test));
	singleton_lists(TESTS_LIST, tests);
}

t_test_results	test_group(char *group) {
	t_list			*tests = singleton_lists(TESTS_LIST, 0x0), *tmp;
	t_test			*ptr;
	t_test_results	res;
	size_t			tab;
	char			*s_tmp;

	res.total = res.success = res.failed = 0;
	title(group);
	list_for_each(tests, tmp, ptr) {
		if (!strcmp(ptr->group, group)) {
			res.total++;
			info("Testing %s ...", ptr->name);
			for (tab = strlen(ptr->name); tab < 62; tab++, printf(" "));
			if ((s_tmp = ptr->fn_test())) {
				printf("[ \033[1;31mFAILED\033[0m ]\n");
				warning("\033[0;37m%s\033[0m\n", s_tmp);
				free(s_tmp);
				res.failed++;
			} else {
				printf("[ \033[1;32mOK\033[0m ]\n");
				res.success++;
			}
		}
	}
	if (!res.total) {
		warning("Could not find any registered tests in %s group.\n", group);
	} else {
		info("Results: Total: %d, Success: %d, Failed: %d. COVERAGE: %d%%\n",
			res.total, res.success, res.failed, (res.success * 100) / res.total);
	}
	return res;
}

void		test_all(void) {
	t_list			*tests = singleton_lists(TESTS_LIST, 0x0), *tmp, *groups = 0x0;
	t_test			*ptr;
	t_test_results	res;
	size_t			total = 0, success = 0, failed = 0;

	list_for_each(tests, tmp, ptr) {
		if (!list_get(groups, ptr->group, strlen(ptr->group))) {
			res = test_group(ptr->group);
			total += res.total;
			success += res.success;
			failed += res.failed;
			list_add(groups, ptr->group, strlen(ptr->group));
		}
	}
	if (!total)
		warning("No tests registered, skipping.\n");
	else {
		printf("\n");
		title("RESULTS");
		info("\033[1;32mTESTS SUCCESS\033[0m:\t%d\n", success);
		info("\033[1;31mTESTS FAILED\033[0m:\t\t%d\n", failed);
		info("\033[1;34mTOTAL COVERAGE\033[0m:\t%d%%\n", (success * 100) / total);
	}
}
