
#ifndef SCANLINE_HPP
# define SCANLINE_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Segment.hpp"
# include "RasterSubject.hpp"

class Scanline {
public:
	Scanline(RasterSubject const &subject);
	u32	getY() const;
	void	move();
	void	render(int *out);//size = 240
	Segment	*begin();
	Segment	*end();
	Segment const	*begin() const;
	Segment const	*end() const;
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

	void	update();
	void	detachOutgoing();
	void	mergeIncoming();
	void	realign(Segment *segment);
	void	insert(Segment *pos, Segment *src);
};

#endif
