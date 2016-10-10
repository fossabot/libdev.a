#ifndef __LIBDEV__
# define __LIBDEV__
# include <stdlib.h>
# include <string.h>
# include <execinfo.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

/* DEFINES */
# define list_add(ptr, member, sizeZ) ptr = list_add_member(ptr, member, sizeZ);

# define list_for_each(org_list, temp, p_tr)\
			for (temp = org_list, p_tr = temp->member;\
			temp && (p_tr = temp->member); temp = temp->next)

# define list_for_each_rev(org_list, temp, p_tr)\
			for (temp = list_get_last(org_list), p_tr = temp->member;\
			temp != temp->head && (p_tr = temp->member); temp = temp->prev)

# define list_tail(org_list, p_tr) ptr = list_get_last(org_list)->member;

# define list_add_after(org_list, p_tr1, p_tr2, sizeZ) org_list = list_insert_after(org_list, p_tr1, p_tr2, sizeZ);

# define list_add_before(org_list, p_tr1, p_tr2, sizeZ) org_list = list_insert_before(org_list, p_tr1, p_tr2, sizeZ);

# define BACKTRACE_SIZE 10

# define L_ASSERT(condition)\
{\
	if (!condition) {\
		warning("Assertion (%s) failed at %s:%d\n", #condition, __FILE__, __LINE__);\
		warning("Function: %s\n", __FUNCTION__);\
		warning("Backtrace:\n");\
		print_trace();\
	}\
}

# define TEST(name) char		*test_##name(void)
# define reg_test(group, name) register_test(group, &test_##name, #name);
# define T_ASSERT(condition, error_name) {\
	if (!condition) {\
		char	*ret = malloc(250);\
		sprintf(ret, "\t%s: Test: '%s', File %s:%d", error_name, #condition, __FILE__, __LINE__);\
		return (ret);\
	}\
}
# define TESTS_LIST 0x1
# define TEST_SUCCESS 0x0

/* TYPEDEFS */
// Signed
typedef signed char			s8_t;
typedef signed short		s16_t;
typedef signed int			s32_t;
typedef signed long long	s64_t;

// Unsigned
typedef unsigned char		u8_t;
typedef unsigned short		u16_t;
typedef unsigned int		u32_t;
typedef unsigned long long	u64_t;

/* STRUCTS */
typedef struct		s_list {
	void				*member;	// Actual member
	size_t				size; 		// Size of the member
	struct s_list		*next;		// Next in list
	struct s_list		*prev;		// Prev in list
	struct s_list		*head;		// Head of the list
}					t_list;

typedef struct		s_singleton {
	u_char				type;		// List type (ENUM)
	t_list				*ptr;		// Actual pointer to the list
}					t_singleton;

typedef struct		s_test {
	char				*(*fn_test)(void);
	char				*group;
	char				*name;
}					t_test;

typedef struct		s_test_results {
	size_t				success;
	size_t				failed;
	size_t				total;
}					t_test_results;


/* FUNCTIONS DEFINITIONS */
// lists.c
t_list		*list_add_member(t_list *list, void *member, size_t size);
t_list		*list_get_last(t_list *list);
t_list		*list_insert_after(t_list *org, t_list *ptr, void *member, size_t size);
t_list		*list_insert_before(t_list *org, t_list *ptr, void *member, size_t size);
size_t		list_size(t_list *list);
void		*list_get(t_list *list, void *ptr, size_t size);

// singleton.c
t_list		*singleton_lists(u_char list_type, t_list *ptr);

// print.c
void		error(char *str, ...);
void		info(char *str, ...);
void		warning(char *str, ...);
void		print_trace(void);

// tests.c
void			register_test(char *group, char *(*test)(void), char *name);
t_test_results	test_group(char *group);

#endif /* __LIBDEV__ */
