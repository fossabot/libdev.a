#include <libdev.h>

enum {
	S_1,
	S_2
};

TEST(list_add_null) {
	t_list	*ptr = 0x0;
	void	*null = 0x0;

	list_add(ptr, null, 0);
	T_ASSERT((ptr == 0x0), "Returned pointer is not null.");
	return TEST_SUCCESS;
}

TEST(list_add_member) {
	t_list	*ptr = 0x0;
	char	test[] = "Hello !\n";

	list_add(ptr, test, 8);
	T_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Member have an unexpected value.");
	T_ASSERT((ptr->size == 8), "Size is wrong");
	return TEST_SUCCESS;
}

TEST(list_add_member_head_list) {
	t_list	*ptr = 0x0;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	T_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head of the list is a wrong pointer.");
	T_ASSERT(!ptr->prev, "Head of the list prev pointer is not null");
	return TEST_SUCCESS;
}

TEST(list_add_member_test_multiples) {
	t_list	*ptr = 0x0;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	T_ASSERT(!strcmp(ptr->next->member, "Hello2 !\n"), "Member have an unexpected value.");
	T_ASSERT(!strcmp(ptr->next->prev->member, "Hello !\n"), "Member have an unexpected value.");
	T_ASSERT(!(ptr->next->head == ptr), "Head pointer is not right");
	return TEST_SUCCESS;
}

TEST(list_for_each) {
	t_list	*ptr = 0x0, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	*s_tmp;
	size_t	i = 0;

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	list_for_each(ptr, tmp, s_tmp) {
		switch (i) {
			case 0: T_ASSERT(s_tmp, "Hello !\n"); break;
			case 1: T_ASSERT(s_tmp, "Hello2 !\n"); break;
			case 2: T_ASSERT(s_tmp, "Hello3 !\n"); break;
			case 3: T_ASSERT(0, "list_for_each too many iterations.");
		}
	}
	return TEST_SUCCESS;
}

TEST(list_tail) {
	t_list	*ptr = 0x0, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";

	tmp = list_tail(ptr);
	T_ASSERT(!tmp, "Pointer is not null.");
	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	tmp = list_tail(ptr);
	T_ASSERT(!strcmp(tmp->member, "Hello3 !\n"), "Tail is wrong.");
	return TEST_SUCCESS;
}

TEST(list_add_after) {
	t_list	*ptr = 0x0, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	test4[] = "Hello2.5 !\n";
	char	test5[] = "Hello4 !\n";

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	list_add_after(ptr, ptr->next, test4, 11);
	T_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head is wrong.");
	T_ASSERT(!strcmp(ptr->next->member, "Hello2 !\n"), "Order is wrong.");
	T_ASSERT(!strcmp(ptr->next->next->member, "Hello2.5 !\n"), "Order is wrong.");
	T_ASSERT(!strcmp(ptr->next->next->next->member, "Hello3 !\n"), "Order is wrong.");
	tmp = list_tail(ptr);
	list_add_after(ptr, tmp, test5, 9);
	tmp = list_tail(ptr);
	T_ASSERT(!strcmp(tmp->member, "Hello4 !\n"), "Order is wrong.");
	T_ASSERT(!tmp->next, "Next pointer is wrong.");
	return TEST_SUCCESS;
}

TEST(list_add_before) {
	t_list	*ptr = 0x0, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	test4[] = "Hello2.5 !\n";
	char	test5[] = "Hello4 !\n";

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	list_add_before(ptr, ptr->next, test4, 11);
	T_ASSERT(!strcmp(ptr->member, "Hello !\n"), "Head is wrong.");
	T_ASSERT(!strcmp(ptr->next->member, "Hello2.5 !\n"), "Order is wrong.");
	T_ASSERT(!strcmp(ptr->next->next->member, "Hello2 !\n"), "Order is wrong.");
	T_ASSERT(!strcmp(ptr->next->next->next->member, "Hello3 !\n"), "Order is wrong.");
	list_add_before(ptr, ptr, test5, 9);
	tmp = ptr->head;
	T_ASSERT(!strcmp(tmp->member, "Hello4 !\n"), "Order is wrong.");
	T_ASSERT(!tmp->prev, "Next pointer is wrong.");
	return TEST_SUCCESS;
}

TEST(list_for_each_rev) {
	t_list	*ptr = 0x0, *tmp;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";
	char	*s_tmp;
	size_t	i = 0;

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	list_for_each_rev(ptr, tmp, s_tmp) {
		switch (i) {
			case 0: T_ASSERT(s_tmp, "Hello3 !\n"); break;
			case 1: T_ASSERT(s_tmp, "Hello2 !\n"); break;
			case 2: T_ASSERT(s_tmp, "Hello !\n"); break;
			case 3: T_ASSERT(0, "list_for_each too many iterations.");
		}
	}
	return TEST_SUCCESS;
}

TEST(list_size) {
	t_list	*ptr = 0x0;
	char	test[] = "Hello !\n";
	char	test2[] = "Hello2 !\n";
	char	test3[] = "Hello3 !\n";

	list_add(ptr, test, 8);
	list_add(ptr, test2, 9);
	list_add(ptr, test3, 9);
	T_ASSERT(list_size(ptr) == 3, "Size is wrong.");
	return TEST_SUCCESS;
}

TEST(s8_t) {
	s8_t	l;
	T_ASSERT(sizeof(l) == 1, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(u8_t) {
	u8_t	l;
	T_ASSERT(sizeof(l) == 1, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(s16_t) {
	s16_t	l;
	T_ASSERT(sizeof(l) == 2, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(u16_t) {
	u16_t	l;
	T_ASSERT(sizeof(l) == 2, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(s32_t) {
	s32_t	l;
	T_ASSERT(sizeof(l) == 4, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(u32_t) {
	u32_t	l;
	T_ASSERT(sizeof(l) == 4, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(s64_t) {
	s64_t	l;
	T_ASSERT(sizeof(l) == 8, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(u64_t) {
	u64_t	l;
	T_ASSERT(sizeof(l) == 8, "Wrong size.");
	return TEST_SUCCESS;
}

TEST(singleton_set) {
	char	*ptr = malloc(10);
	char	*ptr2 = malloc(10);

	T_ASSERT(ptr && ptr2, "Malloc failed");
	strcpy(ptr, "Test123");
	strcpy(ptr2, "Test1234");
	T_ASSERT(!singleton_lists(S_1, ptr), "Return is not null.");
	T_ASSERT(!singleton_lists(S_2, ptr2), "Return is not null.");
	return TEST_SUCCESS;
}

TEST(singleton_get) {
	char	*ptr, *ptr2;

	ptr = singleton_lists(S_1, 0x0);
	ptr2 = singleton_lists(S_2, 0x0);
	T_ASSERT(!strcmp(ptr, "Test123"), "Wrong Value.");
	T_ASSERT(!strcmp(ptr2, "Test1234"), "Wrong Value.");
	free(ptr); free(ptr2);
	return TEST_SUCCESS;
}

TEST(singleton_replace) {
	char	*ptr = malloc(10);

	T_ASSERT(ptr, "Malloc failed");
	strcpy(ptr, "Test12345");
	singleton_lists(S_1, ptr);
	ptr = 0x0;
	ptr = singleton_lists(S_1, 0x0);
	T_ASSERT(!strcmp(ptr, "Test12345"), "Wrong Value.");
	return TEST_SUCCESS;
}

int		main(void) {
	reg_test("linked_list", list_add_null);
	reg_test("linked_list", list_add_member);
	reg_test("linked_list", list_add_member_head_list);
	reg_test("linked_list", list_add_member_test_multiples);
	reg_test("linked_list", list_for_each);
	reg_test("linked_list", list_tail);
	reg_test("linked_list", list_add_after);
	reg_test("linked_list", list_add_before);
	reg_test("linked_list", list_for_each_rev);
	reg_test("linked_list", list_size);
	reg_test("types", s8_t);
	reg_test("types", u8_t);
	reg_test("types", s16_t);
	reg_test("types", u16_t);
	reg_test("types", s32_t);
	reg_test("types", u32_t);
	reg_test("types", s64_t);
	reg_test("types", u64_t);
	reg_test("singletons", singleton_set);
	reg_test("singletons", singleton_get);
	reg_test("singletons", singleton_replace);

	test_all();
	return 0;
}
