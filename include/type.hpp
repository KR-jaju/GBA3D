
#ifndef TYPE_HPP
# define TYPE_HPP

# ifndef NULL
#  define NULL 0
# endif

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;

typedef signed char			i8;
typedef signed short		i16;
typedef signed int			i32;

//--Renderer specific--

#ifndef RENDERER_WIDTH
# define RENDERER_WIDTH 240
#endif
#ifndef RENDERER_HEIGHT
# define RENDERER_HEIGHT 160
#endif
#ifndef MAX_FACE_COUNT
# define MAX_FACE_COUNT 1024
#endif
#ifndef DEPTH_LAYER_SIZE
# define DEPTH_LAYER_SIZE	512
#endif

#define IWRAM_CODE	
// #define IWRAM_CODE __attribute__((section(".iwram"), short_call))
#define INLINE	__attribute__((always_inline))

#endif
