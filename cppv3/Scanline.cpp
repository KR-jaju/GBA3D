
#include "Scanline.hpp"
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


	Segment *p = this->begin();
	for (int i = 0; i < 4; ++i) {
		std::cout << p << ", ";
		p = p->next;
	}

	Event	*&in = this->entry[0];
	while (in != NULL) {
		this->insert(this->end(), &in->segment);
		{in = in->next;}
		std::cerr << "Inserted : " << this->y << std::endl;
	} //insertion
}

u32	Scanline::getY() const {
	return (this->y);
}

void	Scanline::move() {
	this->y += 1;
	if (this->y >= RENDERER_HEIGHT)
		return ;
	// for (Segment *s = this->begin(); s != this->end(); s = s->next)
	// 	std::cout << s << ", ";
	// std::cout << this->end() << std::endl;
	// this->detachOutgoing();
	this->mergeIncoming();
	std::cerr << this->begin() << "--" << this->begin()->next << ",," << this->y << std::endl;
}

void	Scanline::update() {
	// this->detachOutgoing();
	// this->mergeIncoming();
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
	Event	*&out = this->exit[this->y - 1];

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


// for (Segment *s = this->begin(); s != this->end(); s = s->next)
// 		std::cout << s << ", ";
		// <<"|"<< s->next<<"|"<<s->next->next << ", ";
	// std::cout << this->end() << std::endl;

	Segment	*next = curr->next;

	while (curr != this->end()) {
		curr->move(); //update segment
		this->realign(curr);
		// while (in != NULL && in->segment.edge[0].x < curr->edge[0].x) {
		// 	this->insert(curr, &in->segment);
		// 	{in = in->next;}
		// 	std::cerr << "Inserted : 2" << this->y << std::endl;
		// } //insertion
		{curr = next; next = next->next;}
	}
	// while (in != NULL) {
	// 	this->insert(this->end(), &in->segment);
	// 	{in = in->next;}
	// 	std::cerr << "Inserted : " << this->y << std::endl;
	// } //insertion
}

void	Scanline::realign(Segment *s) {
	while (s != this->begin() && s->edge[0].x < s->prev->edge[0].x) {
		Segment*const	p = s->prev;
		Segment*const	pp = p->prev;
		Segment*const	n = s->next;
		
		pp->next = s;
		s->prev = pp;
		s->next = p;
		p->prev = s;
		p->next = n;
		n->prev = p;
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
