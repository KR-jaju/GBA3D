
#include "Scanline.hpp"

Scanline::Scanline(RasterSubject const &subject): entry(), exit(), asl(), y(0) {
	for (u32 i = 0; i < subject.polygon_count; ++i) {
		u32 const	min_y = subject.polygon[i].vertex[0].y >> 3;

		Event	&event = (this->event[i] = Event {
			this->entry[y],
			Segment().init(&subject.polygon[i])
		});
		this->entry[min_y] = &event;
	}
	Event	*&in = this->entry[this->y];
	while (in != NULL) {
		this->insert(this->end(), &in->segment);
		{in = in->next;}
	} //insertion
}

u32	Scanline::getY() const {
	return (this->y);
}

void	Scanline::move() {
	this->y += 1;
	this->update();
}

void	Scanline::update() {
	this->detachOutgoing();
	this->mergeIncoming();
}

void	Scanline::render(int *out) {
	
}

Segment	*Scanline::begin() {
	return (this->asl.next); //TODO: asl.next
}
Segment	*Scanline::end() {
	return (&this->asl);
}

Segment const	*Scanline::begin() const {
	return (this->asl.next); //TODO: asl.next
}
Segment const	*Scanline::end() const {
	return (&this->asl);
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
		while (in != NULL && in->segment.trace[0].x < curr->trace[0].x) {
			this->insert(curr, &in->segment);
			{in = in->next;}
		} //insertion
		this->realign(curr);
		{curr = next; next = next->next;}
	}
	while (in != NULL) {
		this->insert(this->end(), &in->segment);
		{in = in->next;}
	} //insertion
}

void	Scanline::realign(Segment *segment) {
	while (segment != this->begin() && segment->trace[0].x < segment->prev->trace[0].x) {
		Segment*const	prev = segment->prev;
		Segment*const	pp = prev->prev;
		Segment*const	nn = segment->next;

		prev->next = nn;
		prev->prev = segment;
		segment->next = prev;
		segment->prev = pp;
	} //alignment
}

void	Scanline::insert(Segment *pos, Segment *src) {
	Segment*const	prev = pos->prev;
	Segment*const	next = pos;

	prev->next = src;
	next->prev = src;
	src->prev = prev;
	src->next = next;
}
