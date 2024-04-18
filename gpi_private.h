
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
	t_trace	*next;
	t_trace	*pair;
	int	error;
	int	x;
	int	dx;
	int	dy;
	int	step;
}; // 28

struct s_span {
	t_trace *left;
	t_trace *right;
	int		end;
};

struct s_scanline {
	t_span	*global;
	t_span	*active;
	int		y;
};

t_trace	*trace_init(t_trace *self);
void	trace_move(t_trace *self);

t_span	*span_init(t_span *self, t_trace *left, t_trace *right);
void	span_move(t_span *self);

t_scanline	scanline_init(t_trace *global);

