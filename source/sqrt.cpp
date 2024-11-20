#include "gba_math.h"

fixed  sqrt_fx(fixed f) {
   fixed l = 0;
   fixed r = (f.num < (1 << FIX_SHIFT)) ? 1 : fixed::from(f.num + 1);
   fixed m;

   while (l.num != r.num - 1) {
      m = (l + r) >> 1;
      if (m * m <= f)
         l = m;
      else
         r = m;
   }
   return (l);
}