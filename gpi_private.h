
#pragma once

# ifndef NULL
#  define NULL 0
# endif

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
typedef struct s_scanline	t_scanline;


struct s_vertex {
	i32	x;
	i32	y;
	i32	z;
};

struct s_triangle {
	t_vertex	*vertices[3];
};

struct s_trace {
	i32	error;
	i32	x;
	i32	dx;
	i32	dy;
};

struct s_span {
	t_triangle	*triangle;
	t_trace		trace[2];
	i32			start;
	i32			breakpoint;
	i32			end;
	i32			barycentric[3];
};

struct s_scanline {
	t_span	*future_span;
	t_span	*active_span;
	t_span	*active_span_end;
	i32		y;
};






// typedef struct 
typedef struct s_vao		t_vao;
typedef struct s_triangle	t_triangle;
typedef struct s_drawcall	t_drawcall;
typedef struct s_vertex		t_vertex;
typedef struct s_span		t_span;
typedef struct s_trace		t_trace;
typedef struct s_scanline	t_scanline;

typedef struct s_pixel		t_pixel;
typedef struct s_scanpixel	t_scanpixel;

typedef struct s_rasterizer	t_rasterizer;

struct s_vertex {
	i32	x;
	i32	y;
	i32	z;
};

struct s_triangle {
	t_vertex	*vertex[3];
	i32			dwdx[3];
	i32			dwdy[3];
};

struct s_vao {
	t_vertex	vertex[1024];
	t_triangle	triangle[1024];
	i32			triangle_count;
};

/*
dx/dy * (y - y0) = (x - x0)
dx/dy * (y - y0) = a|X| + b X
1. dx/dy * Y = (a + b) X -> (dx/dy) / (a + b)
2. dx/dy * Y = (-a + b)X -> (dx/dy) / (-a+b)

dx * (y - y0) = dy * (x - x0)

*/

struct s_span {
	t_triangle	*ref;
	t_span		*prev;
	t_span		*next;
	i32			dx[2][2];
	i32			dy[2][2]; // up/down, left/right
	i32			error[2];
	i32			w[3]; // barycentric weight
	i32			x[2]; // left, right x
	i32			*y;
	i32			z[2]; // left, right z
	i32			y_start;
	i32			y_center; // 8 precision
	i32			y_end;
};

struct s_scanline {
	t_span		pool[1024];
	t_span		*global;
	t_span		*active;
	t_span		*active_end;
	i32			y;
};

struct s_pixel {
	t_span		*ref;
	t_pixel		*prev;
	t_pixel		*next;
	i32			z;
	i32			w[3];
	i32			end_x;
};

struct s_scanpixel {
	t_pixel	pool[MAX_TRIANGLE_COUNT];
	t_pixel	*global;
	t_pixel	*active;
	t_pixel	*active_end;
	i32		x;
};

// t_drawcall	*drawcall_init(t_drawcall *self, t_vertex *vertices, int *indices);

t_span		*span_init(t_span *self, t_vertex *vertices[3]);
void		span_move(t_span *self, i32 y);

t_scanline	*scanline_init(t_scanline *self, t_triangle *triangles, i32 count);
void		scanline_move(t_scanline *self);
//private
void		scanline_remove(t_scanline *self, t_span *span);
void		scanline_realign(t_scanline *self, t_span *span);
void		scanline_splice(t_scanline *self, t_span *span);
void		scanline_splice_back(t_scanline *self);

t_pixel		*pixel_init(t_pixel *self, t_span *span);
void		pixel_move(t_pixel *self);

t_scanpixel	*scanpixel_init(t_scanpixel *self, t_span *span);
void		scanpixel_move(t_scanpixel *self);
//private
void		scanpixel_remove(t_scanpixel *self, t_pixel *pixel);
void		scanpixel_realign(t_scanpixel *self, t_pixel *pixel);
void		scanpixel_splice(t_scanpixel *self, t_pixel *pixel);
void		scanpixel_splice_back(t_scanpixel *self);