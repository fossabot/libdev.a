#include <libdev.h>

t_list		*list_add_member(t_list *list, void *member, size_t size) {
	t_list		*n_member, *tmp;

	n_member = malloc(sizeof(t_list));
	n_member->member = malloc(size);
	assert(n_member && n_member->member);
	memcpy(n_member->member, member, size);
	n_member->size = size;
	n_member->next = n_member->prev = 0x0;
	if (!list) {
		n_member->head = n_member;
		return n_member;
	}
	for (tmp = list; tmp->next; tmp = tmp->next);
	tmp->next = n_member;
	n_member->prev = tmp;
	n_member->head = list;
	return list;
}

t_list		*list_get_last(t_list *list) {
	t_list		*tmp;

	if (!list)
		return 0x0;
	for (tmp = list; tmp->next; tmp = tmp->next);
	return tmp;
}

t_list		*list_insert_after(t_list *org, t_list *ptr, void *member, size_t size) {
	t_list		*n_member, *tmp, *tmp2;

	n_member = malloc(sizeof(t_list));
	n_member->member = malloc(size);
	assert(n_member && n_member->member);
	memcpy(n_member->member, member, size);
	n_member->size = size;
	n_member->next = n_member->prev = 0x0;
	if (!org) {
		n_member->head = n_member;
		return n_member;
	}
	for (tmp = org; tmp->next && tmp != ptr; tmp = tmp->next);
	if (!tmp->next) {
		tmp->next = n_member;
		n_member->prev = tmp;
	} else {
		tmp2 = tmp->next;
		tmp->next = n_member;
		n_member->prev = tmp;
		tmp2->prev = n_member;
	}
	n_member->head = org;
	return org;
}

t_list		*list_insert_before(t_list *org, t_list *ptr, void *member, size_t size) {
	t_list		*n_member, *tmp, *tmp2;

	n_member = malloc(sizeof(t_list));
	n_member->member = malloc(size);
	assert(n_member && n_member->member);
	memcpy(n_member->member, member, size);
	n_member->size = size;
	n_member->next = n_member->prev = 0x0;
	if (!org) {
		n_member->head = n_member;
		return n_member;
	}
	for (tmp = org; tmp->next && tmp != ptr; tmp = tmp->next);
	if (!tmp->next) {
		tmp->next = n_member;
		n_member->prev = tmp;
	} else {
		tmp2 = tmp->prev;
		n_member->next = tmp;
		tmp->prev = n_member;
		tmp2->next = n_member;
	}
	n_member->head = org;
	return org;
}

size_t		list_size(t_list *list) {
	size_t		i;
	t_list		*tmp;

	if (!list)
		return 0;
	for (tmp = list, i = 0; tmp; tmp = tmp->next, i++);
	return i;
}
