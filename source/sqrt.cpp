#include "gbamath/gbamath.h"

f32  sqrt_fx(f32 f) {
   f32 l = 0;
   f32 r = (f.num < (1 << f32::FIX_SHIFT)) ? 1 : f32::from(f.num + 1);
   f32 m;

   while (l.num != r.num - 1) {
      m = (l + r) >> 1;
      if (m * m <= f)
         l = m;
      else
         r = m;
   }
   return (l);
}