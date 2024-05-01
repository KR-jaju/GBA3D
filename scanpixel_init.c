
#include "gpi_private.h"

/*
문제
1. span리스트가 z를 가지면 해결
*/


t_scanpixel	*scanpixel_init(t_scanpixel *self, t_span *span) {
	self->global = span;
	self->active = &self->active_end;
	self->active_end = NULL;
	self->x = 0;
	scanpixel_splice_back(self);
	return (self);
}
