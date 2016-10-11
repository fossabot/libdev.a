#include <libdev.h>

void		*singleton_lists(u_char list_type, void *ptr) {
	t_list			*tmp;
	t_singleton		*member;
	static t_list	*index = 0x0;

	if (ptr) {
		if (!list_size(index)) {
			member = malloc(sizeof(t_singleton));
			L_ASSERT(member);
			member->ptr = ptr;
			member->type = list_type;
			list_add(index, member, sizeof(t_singleton));
		} else {
			list_for_each(index, tmp, member) {
				if (member->type == list_type) {
					member->ptr = ptr;
					return 0x0;
				}
			}
			member = malloc(sizeof(t_singleton));
			L_ASSERT(member);
			member->ptr = ptr;
			member->type = list_type;
			list_add(index, member, sizeof(t_singleton));
		}
	} else {
		if (!list_size(index))
			return 0x0;
		list_for_each(index, tmp, member) {
			if (member->type == list_type)
				return member->ptr;
		}
	}
	return 0x0;
}
