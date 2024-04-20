
#pragma once

# ifndef NULL
#  define NULL 0
# endif

typedef signed char		i8;
typedef signed short	i16;
typedef signed int		i32;

typedef struct s_trace		t_trace;
typedef struct s_span		t_span;
typedef struct s_pixel		t_pixel;
typedef struct s_slice		t_slice;
typedef struct s_scanline	t_scanline;
typedef struct s_scanpixel	t_scanpixel;

struct s_trace {
	i32	error;
	i32	x;
	i32	dx;
	i32	dy;
};

struct s_span {
	t_span	*prev;
	t_span	*next;
	t_trace *left;
	t_trace *right;
	i32		min_y;
	i32		max_y;
};

struct s_scanline {
	t_span	*global;
	t_span	*active;
	t_trace	end_trace;
	t_span	active_end;
	i32		y;
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

t_span	*span_init(t_span *self, t_trace *left, t_trace *right, i32 min_y, i32 max_y);
void	span_move(t_span *self);

t_scanline	*scanline_init(t_scanline *self);
void		scanline_push(t_scanline *self, t_span *span);
void		scanline_sort(t_scanline *self);
void		scanline_move(t_scanline *self);
void		scanline_realign(t_scanline *self, t_span *span);
void		scanline_remove(t_scanline *self, t_span *span);
void		scanline_splice(t_scanline *self, t_span *span);

t_pixel		*pixel_init(t_pixel *self);
void		pixel_move(t_pixel *self);

t_slice		slice_init(t_slice *self);
void		slice_move(t_slice *self);

t_scanpixel	*scanpixel_init(t_scanpixel *self, t_span *span_set);
void		scanpixel_move(t_scanpixel *self);
void		scanpixel_realign(t_scanpixel *self, t_slice *slice);
void		scanpixel_remove(t_scanpixel *self, t_slice *slice);
void		scanpixel_splice(t_scanpixel *self, t_slice *slice);



