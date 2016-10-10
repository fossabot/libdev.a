#include <libdev.h>

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
	T_ASSERT((ptr->next->head == ptr), "Head pointer is not right");
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




int		main(void) {
	reg_test("linked_list", list_add_null);
	reg_test("linked_list", list_add_member);
	reg_test("linked_list", list_add_member_head_list);
	reg_test("linked_list", list_add_member_test_multiples);
	reg_test("linked_list", list_for_each);
	reg_test("linked_list", list_tail);
	reg_test("linked_list", list_add_after);

	test_all();
	return 0;
}
