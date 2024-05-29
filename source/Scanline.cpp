
#include "Scanline.hpp"
#include "Shader.hpp"
#include <iostream>

Scanline::Scanline(RasterSubject const &subject): entry(), exit(), asl(), y(0) {
	for (u32 i = 0; i < subject.polygon_count; ++i) {
		u32 const	min_y = subject.polygon[i].vertex[0].y >> 3;
		Event		&event = this->event[i];
		Event		**entry = &this->entry[min_y];
	
		event.segment.init(&subject.polygon[i]);
		while (*entry != NULL && (*entry)->segment.edge[0].x < event.segment.edge[0].x) {
			entry = &(*entry)->next;
		}
		event.next = *entry;
		*entry = &event;
	}
	Event	*&in = this->entry[0];
	while (in != NULL) {
		Event	*next = in->next;
	
		this->insert(this->end(), &in->segment);
		u32 y = in->segment.triangle->vertex[2].y >> 3;
		in->next = this->exit[y];
		this->exit[y] = in;
		{in = next;}
	} //insertion
}

// void	Scanline::move() {
// 	this->detachOutgoing();
// 	this->y += 1;
// 	if (this->y >= RENDERER_HEIGHT)
// 		return ;
// 	this->mergeIncoming();
// }

void	Scanline::render(u16 *out) const {
	this->render(0, 240, NULL, this->begin(), out);
}

void	Scanline::render(int l, int r, Segment const *current, Segment const *incoming, u16 *out) const {
	Segment const* const	end = this->end();
	Segment const			*next;
	static int				x; // TODO: threadlocal

	next = incoming;
	x = l;
	while (x < r) {
		
		if (next != end && x == next->edge[0].x) {
			int const	nl = next->edge[0].x;
			int const	nr = next->edge[1].x;
		
			this->render(nl, nr, next, next->next, out);
			next = next->next;
			while (next != end && x > next->edge[0].x) {
				next = next->next;
			}
			continue;
		}
		// out[x] = (current == NULL);
		// out[x] = (current == NULL) * 15;
		// out[x] = Shader::pixelShader(current, x, this->y);
		x += 1;
	}
}

void	Scanline::detachOutgoing() {
	Event	*&out = this->exit[this->y];

	while (out != NULL) {
		Segment*const	c = &out->segment;
		Segment*const	p = c->prev;
		Segment*const	n = c->next;

		p->next = n;
		n->prev = p;
		{out = out->next;}
	}
}

void	Scanline::mergeIncoming() {
	Event	*&in = this->entry[this->y];
	Segment	*curr = this->begin();
	Segment	*next = curr->next;

	while (curr != this->end()) {
		curr->move(); //update segment
		this->realign(curr);
		while (in != NULL && in->segment.edge[0].x < curr->edge[0].x) {
			Event	*next = in->next;
			this->insert(curr, &in->segment);
			u32 y = in->segment.triangle->vertex[2].y >> 3;
			in->next = this->exit[y];
			this->exit[y] = in;
			{in = next;}
		} //insertion
		{curr = next; next = next->next;}
	}
	while (in != NULL) {
		Event	*next = in->next;
		this->insert(this->end(), &in->segment);
		u32 y = in->segment.triangle->vertex[2].y >> 3;
		in->next = this->exit[y];
		this->exit[y] = in;
		{in = next;}
	} //insertion
}

// void	Scanline::realign(Segment *s) {
// 	while (s != this->begin() && s->edge[0].x < s->prev->edge[0].x) {
// 		Segment*const	p = s->prev;
// 		Segment*const	pp = p->prev;
// 		Segment*const	n = s->next;
		
// 		pp->next = s;
// 		s->prev = pp;
// 		s->next = p;
// 		p->prev = s;
// 		p->next = n;
// 		n->prev = p;
// 	} //alignment
// }

// void	Scanline::insert(Segment *pos, Segment *src) {
// 	Segment*const	prev = pos->prev;
// 	Segment*const	next = pos;

// 	prev->next = src;
// 	next->prev = src;
// 	src->prev = prev;
// 	src->next = next;
// }
