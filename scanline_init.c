
#include "gpi_private.h"

static
t_span	*to_list(t_scanline *self, t_vao *vao) {
	i32 const	n = vao->triangle_count;
	t_span		*span = self->pool;
	t_span		*prev = NULL;

	for (i32 i = 0; i < n; ++i) {
		span_init(span, vao->triangle[n].vertex);
		if (prev != NULL)
			prev->next = span;
		span += 1;
	}
	return (self->pool);
}

static
i32	compare(t_span const *a, t_span const *b) {
	t_trace*const	a_begin = a->shape ? &a->traces[1] : &a->traces[0];
	t_trace*const	b_begin = b->shape ? &b->traces[1] : &b->traces[0];

	if (a->y[0] < b->y[0])
		return (1);
	if (a->y[0] == b->y[0])
		return (a_begin->x < b_begin->x);
	return (0);
}

static
void	split(t_span *head, t_span **a, t_span **b) {
	t_span	*slow = head;
	t_span	*fast = head->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

static
t_span	*merge(t_span *a, t_span *b) {
	t_span	*result = NULL;
	t_span	**tmp = &result;

	while (a != NULL && b != NULL) {
		if (compare(a, b)) {
			*tmp = a;
			tmp = &a->next;
			a = a->next;
		} else {
			*tmp = b;
			tmp = &b->next;
			b = b->next;
		}
	}
	while (a != NULL) {
		*tmp = a;
		tmp = &a->next;
		a = a->next;
	}
	while (b != NULL) {
		*tmp = b;
		tmp = &b->next;
		b = b->next;
	}
	*tmp = NULL;
	return (result);
}

static
void	merge_sort(t_span **head_ref) {
	t_span	*head = *head_ref;
	t_span	*a;
	t_span	*b;

	if (head == NULL || head->next == NULL)
		return ; //base case
	split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = merge(a, b);
	return (*head_ref);
}

static
t_span	*convert(t_scanline *self, t_vao *vao) {
	t_span	*unsorted = to_list(self, vao);
	merge_sort(&unsorted);

	return (unsorted);
}

t_scanline	*scanline_init(t_scanline *self, t_vao *vao) {
	self->pool_end = self->pool;
	self->global = convert(self, vao);
	self->active = (t_span *)&self->active_end;
	self->active_end = NULL;
	return (self);
}