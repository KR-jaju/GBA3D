#include "math.c"

void S_matrix_init(float matrix[16],Vec3 scale)
{
    matrix4x4scaler(matrix,scale);
}

void R_matrix_init(float matrix[16], Vec3 rotate)
{
    matrix4x4rotateYPR(matrix, rotate);
}

void T_matrix_init(float matrix[16], Vec3 trans)
{
    
}