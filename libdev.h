#ifndef __LIBDEV__
# define __LIBDEV__
# include <stdlib.h>
# include <assert.h>
# include <string.h>

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

/* STRUCTS */
typedef struct		s_list {
	void				*member;	// Actual member
	size_t				size; 		// Size of the member
	struct s_list		*next;		// Next in list
	struct s_list		*prev;		// Prev in list
	struct s_list		*head;		// Head of the list
}					t_list;

/* FUNCTIONS DEFINITIONS */
// lists.c
t_list		*list_add_member(t_list *list, void *member, size_t size);
t_list		*list_get_last(t_list *list);
t_list		*list_insert_after(t_list *org, t_list *ptr, void *member, size_t size);
t_list		*list_insert_before(t_list *org, t_list *ptr, void *member, size_t size);

#endif /* __LIBDEV__ */
