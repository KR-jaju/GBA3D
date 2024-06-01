
#ifndef SCANLINE_HPP
# define SCANLINE_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Segment.hpp"
# include "RasterSubject.hpp"
#include <iostream>

class Scanline {
public:
	IWRAM_CODE
	Scanline(RasterSubject const &subject);
	// IWRAM_CODE
	// void	move();
	IWRAM_CODE
	void	render(u16 *out) const;//size = 240
	

	INLINE void	move() {
		this->detachOutgoing();
		this->y += 1;
		if (this->y >= RENDERER_HEIGHT)
			return ;
		this->mergeIncoming();
	}
	INLINE u32	getY() const {
		return (this->y);
	}
	INLINE Segment	*begin() {
		return (this->asl.next); //TODO: asl.next
	}
	INLINE Segment	*end() {
		return (&this->asl);
	}
	INLINE Segment const	*begin() const {
		return (this->asl.next); //TODO: asl.next
	}
	INLINE Segment const	*end() const {
		return (&this->asl);
	}

private:
	struct Event {
		Event	*next;
		Segment	segment;
	};
	Event	event[512];
	Event	*entry[160];
	Event	*exit[160];
	Segment	asl; //active_segment_list
	u32		y;

	IWRAM_CODE
	void	render(u32 l, u32 r, Segment const *current, Segment const *incoming, u16 *out) const;
	IWRAM_CODE
	void	detachOutgoing();
	IWRAM_CODE
	void	mergeIncoming();
	// IWRAM_CODE
	// void	realign(Segment *segment);
	// IWRAM_CODE
	// void	insert(Segment *pos, Segment *src);

	INLINE void	realign(Segment *s) {
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

	INLINE void	insert(Segment *pos, Segment *src) {
		Segment*const	prev = pos->prev;
		Segment*const	next = pos;

		prev->next = src;
		next->prev = src;
		src->prev = prev;
		src->next = next;
	}
};

#endif
