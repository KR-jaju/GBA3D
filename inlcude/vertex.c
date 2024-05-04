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
    matrix4x4SetTranslation(matrix,trans);
}

void vertex_to_world(Vec3* vertex, const Vec3 *scale, const Vec3 *rotate, const Vec3 *trans)
{
    float matrix[16];
    matrix4x4setIdentity(matrix);
    matrix4x4scaler(matrix, *scale);
    matrix4x4rotateYPR(matrix, *rotate);
    matrix4x4SetTranslation(matrix, *trans);

    vecTransform(matrix,vertex);
}