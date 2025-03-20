
/*
1. unpack (vertex index, address)
2. unpack vertex (u, v, x, y)
3. calculate (dudx, dvdx, dxdy * 2, d(u, v)dy * 2) : 총 8개
(x, y, dudx, dvdx, dxdy, dxdy, 

1. 
x, y, height(y1 - y0), (dxdy01, dxdy02), dudx, dvdx, dudy_left, dvdy_left (9 + 1)
dxdy12, x1, dudy_left, dvdx_left


u_left, v_left, height, (x_left), dxdy_left, dudy_left, dvdy_left, x_right, dxdy_right



height에 triangle major를 적는다.

major에 따라 낮은 삼각형에서 로드할 값이 결정된다.

(height, dxdy_right)만 로드하거나. (height, x_left, dxdy_left, dudy_left, dvdy_left)를 로드함.


*/