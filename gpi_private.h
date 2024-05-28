
#pragma once

# ifndef NULL
#  define NULL 0
# endif

# define SUBPIXEL_PRECISION	8

# define MAX_TRIANGLE_COUNT 1024
# define MAX_DEPTH_LAYER	32

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;

typedef signed char			i8;
typedef signed short		i16;
typedef signed int			i32;

typedef struct s_vertex		t_vertex;
typedef struct s_triangle	t_triangle;
typedef struct s_trace		t_trace;
typedef struct s_span		t_span;
typedef struct s_pixel		t_pixel;
typedef struct s_slice		t_slice;
typedef struct s_scanline	t_scanline;
typedef struct s_fragment	t_fragment;

struct s_vertex {
	i32	x;
	i32	y;
	i32	z;
};

struct s_triangle {
	t_vertex	*vertices[3];
};

t_triangle	*triangle_init(t_triangle *self, t_vertex *a, t_vertex *b, t_vertex *c);

struct s_trace {
	i32	scaled_dx;
	i32	scaled_dy;
	i32	step;
	i32	error;
	i32	x;
};

struct s_pixel {
	i32	depth;
};

struct s_slice
{
	t_slice	*prev;
	t_slice	*next;
	t_pixel	pixel; // TODO?: 메모리 정렬로 인한 낭비 가능성 있음
	i32		min_x;
	i32		max_x;
};

struct s_scanpixel {
	t_span	*span_set;
	t_slice	*slice_set;
	t_slice	slice_set_end;
	i32	x;
};


t_trace	*trace_init(t_trace *self, i32 x0, i32 y0, i32 x1, i32 y1);
void	trace_move(t_trace *self);

struct s_span {
	t_span		*prev;
	t_span		*next;
	t_triangle	*triangle;
	t_trace		trace[2];
	i32			ac_orientation;
	i32			entry;
	i32			breakpoint;
	i32			exit;
	i32			barycentric[3];
};

t_span		*span_init(t_span *self, t_triangle *triangle);
void		span_move(t_span *self, i32 y);

struct s_scanline {
	t_span	*future_span;
	t_span	*active_span;
	t_span	*active_span_end;
	i32		y;
};

t_scanline	*scanline_init(t_scanline *self, t_triangle *triangles, i32 count);
void		scanline_move(t_scanline *self);
//private
void		scanline_remove(t_scanline *self, t_span *span);
void		scanline_realign(t_scanline *self, t_span *span);
void		scanline_splice(t_scanline *self, t_span *span);
void		scanline_splice_back(t_scanline *self);

struct s_fragment {
	t_fragment	*prev;
	t_fragment	*next;
	t_triangle	*triangle;
	i32		entry;
	i32		exit;
	i32		depth;
};

t_fragment	*fragment_init(t_fragment *self, t_span *span);
void		fragment_move(t_fragment *self);

struct s_scanpixel
{
	t_fragment	*future_fragment;
	t_fragment	*active_fragment;
	t_fragment	*active_fragment_end;
	i32			x;
};

// t_scanpixel	*scanpixel_init(t_scanpixel *self, t_span *span);
// void		scanpixel_move(t_scanpixel *self);
// //private
// void		scanpixel_remove(t_scanpixel *self, t_fragment *pixel);
// void		scanpixel_realign(t_scanpixel *self, t_fragment *pixel);
// void		scanpixel_splice(t_scanpixel *self, t_fragment *pixel);
// void		scanpixel_splice_back(t_scanpixel *self);
