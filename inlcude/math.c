#pragma onece

#include <stdio.h>
#include <math.h>

typedef struct s_obj t_obj;

const float PI = 3.1415926f;

typedef struct Vec3
{
    float x,y,z;
}Vec3;

struct s_obj
{
    Vec3 vertex[512];
    int size;
};
float getRadian(float num)
{
    return num*(PI/180.0f);
}

Vec3 vecTransformed(const float matrix[16], Vec3 vec) //행렬 변환을 적용
{
    Vec3 transformed;
    transformed.x = (vec.x*matrix[0]) + (vec.y*matrix[1]) + (vec.z*matrix[2]) + matrix[3];
    transformed.y = (vec.x*matrix[4]) + (vec.y*matrix[5]) + (vec.z*matrix[6]) + matrix[7];
    transformed.z = (vec.x*matrix[8]) + (vec.y*matrix[9]) + (vec.z*matrix[10]) + matrix[11];
    float w = (vec.x * matrix[12]) + (vec.x * matrix[13]) + (vec.x * matrix[14]) + matrix[15];

    if(w != 1.0f)
    {
        transformed.x = transformed.x/ w;
        transformed.y = transformed.y/ w;
        transformed.z = transformed.z/ w; 
    }
    return transformed;
}

void vecTransform(const float matrix[16], Vec3* vec) //행렬 변환을 적용
{
    Vec3 transformed;
    transformed.x = (vec->x*matrix[0]) + (vec->y*matrix[1]) + (vec->z*matrix[2]) + matrix[3];
    transformed.y = (vec->x*matrix[4]) + (vec->y*matrix[5]) + (vec->z*matrix[6]) + matrix[7];
    transformed.z = (vec->x*matrix[8]) + (vec->y*matrix[9]) + (vec->z*matrix[10]) + matrix[11];
    float w = (vec->x * matrix[12]) + (vec->x * matrix[13]) + (vec->x * matrix[14]) + matrix[15];

    if(w != 1.0f)
    {
        transformed.x = transformed.x/ w;
        transformed.y = transformed.y/ w;
        transformed.z = transformed.z/ w; 
    }
}

float matrix4x4Get(const float matrix[16], int row, int col) 
{
    return matrix[row * 4 + col];
}

void matrix4x4Set(float matrix[16], int row, int col, float value) 
{
    matrix[row * 4 + col] = value;
}

void matrix4x4Mul(float a[16], const float b[16]) //행렬곱
{
    float result[16];
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            float value = 0.0f;
            for (int i = 0; i < 4; ++i) {
                value = value + matrix4x4Get(a, row, i) * matrix4x4Get(b, i, col);
            }
            matrix4x4Set(result, row, col, value);
        }
    }
    memcpy(a, result, sizeof(result));
}

void matrix4x4setIdentity(float matrix[16]) //기본 행렬 생성
{
    memset(matrix,0,sizeof(*matrix)*16);
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void matrix4x4scaler(float matrix[16],Vec3 scale) //확대축소
{
    matrix[0] = scale.x;
    matrix[5] = scale.y;
    matrix[10] = scale.z;
}

void matrix4x4rotateYPR(float matrix[16],Vec3 rotate) //회전
{
    float tmp[16];
    rotate.x = getRadian(rotate.x);
    rotate.y = getRadian(rotate.y);
    rotate.z = getRadian(rotate.z);
    matrix4x4setIdentity(tmp);
    tmp[0] = (cosf(rotate.z) * cosf(rotate.x)) + (sinf(rotate.z)*sinf(rotate.x)*sinf(rotate.y));
    tmp[1] = -(sinf(rotate.z) * cosf(rotate.x)) + (cosf(rotate.z)*sinf(rotate.x)*sinf(rotate.y));
    tmp[2] = sinf(rotate.x) * cosf(rotate.y);

    tmp[4] = sinf(rotate.z) * cosf(rotate.y);
    tmp[5] = cosf(rotate.z) * cosf(rotate.y);
    tmp[6] = -sinf(rotate.y);

    tmp[8] = (-cosf(rotate.z) * sinf(rotate.z)) + (sinf(rotate.z)*cosf(rotate.x)*sinf(rotate.y));
    tmp[9] = (sinf(rotate.z) * sinf(rotate.z)) + (cosf(rotate.z)*cosf(rotate.x)*sinf(rotate.y));
    tmp[10] = cosf(rotate.y) * cosf(rotate.x);

    matrix4x4Mul(matrix,tmp);
}

void matrix4x4transport(float matrix[16], Vec3 trans)
{
    
}