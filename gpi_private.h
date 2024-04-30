
#pragma once

# ifndef NULL
#  define NULL 0
# endif

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;

typedef signed char			i8;
typedef signed short		i16;
typedef signed int			i32;

// typedef struct 
typedef struct s_vao		t_vao;
typedef struct s_triangle	t_triangle;
typedef struct s_drawcall	t_drawcall;
typedef struct s_vertex		t_vertex;
typedef struct s_span		t_span;
typedef struct s_trace		t_trace;
typedef struct s_scanline	t_scanline;
typedef struct s_rasterizer	t_rasterizer;

struct s_vertex {
	i32	x;
	i32	y;
	i32	z;
};

struct s_triangle {
	t_vertex	*vertex[3];
};

struct s_vao {
	t_vertex	vertex[1024];
	t_triangle	triangle[1024];
	i32			triangle_count;
};

struct s_trace {
	int	error;
	int	x;
	int	dx;
	int	dy;
};

struct s_span {
	t_span		*prev;
	t_span		*next;
	t_trace		traces[3]; //ab, ac, bc 순으로 들어감
	i32			shape; // ac가 왼쪽인가 오른쪽인가
	i32			y[3]; //min_y, center_y, max_y 저장하는 곳, 이름 미정
	t_vertex	*vertex[3];
	i32			weight[3];
};

struct s_scanline {
	t_span		pool[1024];
	t_span		*global;
	t_span		*active;
	t_span		*active_end;
	i32			y;
};

// t_drawcall	*drawcall_init(t_drawcall *self, t_vertex *vertices, int *indices);

t_trace		*trace_init(t_trace *self, i32 x0, i32 y0, i32 x1, i32 y1);
void		trace_move(t_trace *self);

t_span		*span_init(t_span *self, t_vertex *vertices[3]);
void		span_move(t_span *self, i32 y);
t_trace		*span_left(t_span *self, i32 is_upper);
t_trace		*span_right(t_span *self, i32 is_upper);

t_scanline	*scanline_init(t_scanline *self, t_triangle *triangles, i32 count);
void		scanline_move(t_scanline *self);
//private
void		scanline_remove(t_scanline *self, t_span *span);
void		scanline_realign(t_scanline *self, t_span *span);
void		scanline_splice(t_scanline *self, t_span *span);
void		scanline_splice_back(t_scanline *self);

