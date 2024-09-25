#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED
#include <Eigen/Dense>
#include <cmath>

#define __PI__ 3.14159265359

using namespace Eigen;

float grausToRad(float g) {
    return ((g*__PI__)/180.0f);
}

Matrix3f getTranslacao(float tx, float ty) {
    
    Matrix3f M = Matrix3f::Identity();
    M(0, 2) = tx;
    M(1, 2) = ty;

    return M;
}

Matrix3f getEscala(float sx, float sy) {
    
    Matrix3f M = Matrix3f::Identity();
    M(0, 0) = sx;
    M(1, 1) = sy;

    return M;
}

Matrix3f getRotacao(float g) {

    float s = sin(grausToRad(g));
    float c = cos(grausToRad(g));
    
    Matrix3f M = Matrix3f::Identity();
    M(0, 0) = c;
    M(0, 1) = -s;
    M(1, 0) = s;
    M(1, 1) = c;

    return M;
}

Matrix3f getReflexaoX() {
    
    Matrix3f M = Matrix3f::Identity();
    M(1, 1) = -1.0f;

    return M;
}

Matrix3f getReflexaoY() {
    
    Matrix3f M = Matrix3f::Identity();
    M(0, 0) = -1.0f;

    return M;
}

Matrix3f getCissHorizontal(float a) {
    
    Matrix3f M = Matrix3f::Identity();
    M(0, 1) = a;

    return M;
}

Matrix3f getCissVertical(float b) {
    
    Matrix3f M = Matrix3f::Identity();
    M(1, 0) = b;

    return M;
}

#endif