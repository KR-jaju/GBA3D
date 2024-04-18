
#pragma once

# ifndef NULL
#  define NULL 0
# endif

typedef signed char		i8;
typedef signed short	i16;
typedef signed int		i32;

typedef struct s_trace		t_trace;
typedef struct s_span		t_span;
typedef struct s_scanline	t_scanline;

struct s_trace {
	int	error;
	int	x;
	int	dx;
	int	dy;
	int	step;
}; // 28

struct s_span {
	t_span	*prev;
	t_span	*next;
	t_trace *left;
	t_trace *right;
	int		y;
	int		max_y;
};

struct s_scanline {
	t_span	*global;
	t_span	*active;
	t_span	global_tail;
	t_span	aet_head;
	t_span	aet_tail;
	int		y;
};

t_trace	*trace_init(t_trace *self, i32 x0, i32 y0, i32 x1, i32 y1);
void	trace_move(t_trace *self);

t_span	*span_init(t_span *self, t_trace *left, t_trace *right, i32 min_y, i32 max_y);
void	span_move(t_span *self);
i32		span_end(t_span *self);

t_scanline	*scanline_init(t_scanline *self, t_trace *global);
void		scanline_move(t_scanline *self);

