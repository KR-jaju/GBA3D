
#include "gpi_private.h"

//임시함수니까 빠른 시일 내로 처리해야함
void	sort_spans(t_span *array, u32 n) {

}

// #include "gpi_private.h"

//may a be in front of b?
// static
// i32	compare(t_span const *a, t_span const *b) {
// 	return (a->min_y < b->min_y || (a->min_y == b->min_y && a->left->x < b->left->x));
// }

// static
// void	split(t_span *head, t_span **a, t_span **b) {
// 	t_span	*slow = head;
// 	t_span	*fast = head->next;

// 	while (fast != NULL) {
// 		fast = fast->next;
// 		if (fast != NULL) {
// 			slow = slow->next;
// 			fast = fast->next;
// 		}
// 	}
// 	*a = head;
// 	*b = slow->next;
// 	slow->next = NULL;
// }

// static
// t_span	*merge(t_span *a, t_span *b) {
// 	t_span	*result = NULL;
// 	t_span	**tmp = &result;

// 	while (a != NULL && b != NULL) {
// 		if (compare(a, b)) {
// 			*tmp = a;
// 			tmp = &a->next;
// 			a = a->next;
// 		} else {
// 			*tmp = b;
// 			tmp = &b->next;
// 			b = b->next;
// 		}
// 	}
// 	while (a != NULL) {
// 		*tmp = a;
// 		tmp = &a->next;
// 		a = a->next;
// 	}
// 	while (b != NULL) {
// 		*tmp = b;
// 		tmp = &b->next;
// 		b = b->next;
// 	}
// 	*tmp = NULL;
// 	return (result);
// }

// static
// void	merge_sort(t_span **head_ref) {
// 	t_span	*head = *head_ref;
// 	t_span	*a;
// 	t_span	*b;

// 	if (head == NULL || head->next == NULL)
// 		return ; //base case
// 	split(head, &a, &b);
// 	merge_sort(&a);
// 	merge_sort(&b);
// 	*head_ref = merge(a, b);
// }

// void	scanline_sort(t_scanline *self) {
// 	merge_sort(&self->triangle_set);
// }
