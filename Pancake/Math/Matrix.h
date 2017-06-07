#ifndef PANCAKE_MATRIX
#define PANCAKE_MATRIX

#include <memory>
#include <ostream>
#include <iomanip>
#include <iostream>

#include "Vector2.h"

class Matrix {
public:
  Matrix();
  
  Matrix(const Matrix& o);
  
  ~Matrix();
  
  void loadIdentity();
  
  static void translate(Matrix& m, Vector2 v);
  
  static void scale(Matrix& m, Vector2 v);
  
  static void rotateX(Matrix& m, float t);
  
  static void rotateY(Matrix& m, float t);
  
  static void rotateZ(Matrix& m, float t);
  
  static void ortho(Matrix& m, float left, float right, float bottom, float top, float near, float far);
  
  Matrix operator*(const Matrix& o);
  
  void multiply(const Matrix& o);
  
  float data[16] = {0};
  
  float* firstRow[4];
  
  float* secondRow[4];
  
  float* thirdRow[4];
  
  float* fourthRow[4];
  
  float* firstColumn[4];
  
  float* secondColumn[4];
  
  float* thirdColumn[4];
  
  float* fourthColumn[4];

private:
  float combineRowAndColumn(float* row, float* column);
};

#endif
