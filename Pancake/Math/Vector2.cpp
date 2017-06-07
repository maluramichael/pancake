#include "Vector2.h"
#include "Interpolate.h"

Vector2::Vector2() {
}

Vector2::Vector2(float v) : x(v), y(v) {
}

Vector2::Vector2(float x, float y) : x(x), y(y) {
}

Vector2::Vector2(int x, int y) : x(x), y(y) {
}

Vector2 Vector2::operator+(const Vector2& o) const {
  return Vector2(this->x + o.x, this->y + o.y);
}

Vector2 Vector2::operator-(const Vector2& o) const {
  return Vector2(this->x - o.x, this->y - o.y);
}

Vector2 Vector2::operator*(const Vector2& o) const {
  return Vector2(this->x * o.x, this->y * o.y);
}

Vector2 Vector2::operator/(const Vector2& o) const {
  return Vector2(this->x / o.x, this->y / o.y);
}

Vector2 Vector2::operator+(const float& o) const {
  return Vector2(this->x + o, this->y + o);
}

Vector2 Vector2::operator-(const float& o) const {
  return Vector2(this->x - o, this->y - o);
}

Vector2 Vector2::operator*(const float& o) const {
  return Vector2(this->x * o, this->y * o);
}

Vector2 Vector2::operator/(const float& o) const {
  return Vector2(this->x / o, this->y / o);
}
//
//std::ostream& Vector2::operator<<(std::ostream& stream, const Vector2& v) {
//    stream << '(' << v.x << ',' << v.y << ')';
//    return stream;
//}

void Vector2::move(float x, float y) {
  this->x += x;
  this->y += y;
}

void Vector2::add(const Vector2& o) {
  x += o.x;
  y += o.y;
}

void Vector2::subtract(const Vector2& o) {
  x -= o.x;
  y -= o.y;
}

void Vector2::multiply(const Vector2& o) {
  x *= o.x;
  y *= o.y;
}

void Vector2::divide(const Vector2& o) {
  x /= o.x;
  y /= o.y;
}

void Vector2::add(float o) {
  x += o;
  y += o;
}

void Vector2::subtract(float o) {
  x -= o;
  y -= o;
}

void Vector2::multiply(float o) {
  x *= o;
  y *= o;
}

void Vector2::divide(float o) {
  x /= o;
  y /= o;
}

void Vector2::invert() {
  multiply(-1);
}

float Vector2::dot(const Vector2& o) const {
  return ((this->x * o.y) - (o.x * this->y));
}

void Vector2::normalize() {
  double l = length();
  x /= l;
  y /= l;
}

Vector2 Vector2::normalized() {
  double l = length();
  if (l == 0) {
    return Vector2();
  }
  return Vector2(x /= l, y /= l);
}

double Vector2::length() {
  return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2::rotate(float theta) {
  double cs = cos(theta);
  double sn = sin(theta);
  double px = x * cs - y * sn;
  double py = x * sn + y * cs;
  
  x = (float) px;
  y = (float) py;
}

float Vector2::rad() {
  return (float) atan2(y, x);
}

float Vector2::deg() {
  return (float) (atan2(y, x) * (180 / M_PI));
}

Vector2 Vector2::Zero() {
  return Vector2(0, 0);
}

Vector2 Vector2::One() {
  return Vector2(1, 1);
}

Vector2 Vector2::Up() {
  return Vector2(0, -1);
}

Vector2 Vector2::Down() {
  return Vector2(0, 1);
}

Vector2 Vector2::Left() {
  return Vector2(-1, 0);
}

Vector2 Vector2::Right() {
  return Vector2(1, 0);
}

Vector2 Vector2::interpolate(const Vector2& to, float t) {
  //return Vector2(
  //  interpolate(this->x, to.x, t),
  //  interpolate(this->y, to.y, t)
  //);
}

Vector2 Vector2::interpolateCosine(const Vector2& to, float t) {
  //return Vector2(
  //  interpolateCosine(this->x, to.x, t),
  //  interpolateCosine(this->y, to.y, t)
  //);
}
