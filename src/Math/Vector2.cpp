//
// Created by Michael Malura on 10/04/17.
//

#include "../../include/Math/Vector2.h"

Pancake::Math::Vector2::Vector2() {

}

Pancake::Math::Vector2::Vector2(float v) : x(v), y(v) {

}

Pancake::Math::Vector2::Vector2(float x, float y) : x(x), y(y) {

}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator+(const Pancake::Math::Vector2& o) const {
    return Vector2(this->x + o.x, this->y + o.y);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator-(const Pancake::Math::Vector2& o) const {
    return Vector2(this->x - o.x, this->y - o.y);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator*(const Pancake::Math::Vector2& o) const {
    return Vector2(this->x * o.x, this->y * o.y);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator/(const Pancake::Math::Vector2& o) const {
    return Vector2(this->x / o.x, this->y / o.y);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator+(const float& o) const {
    return Vector2(this->x + o, this->y + o);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator-(const float& o) const {
    return Vector2(this->x - o, this->y - o);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator*(const float& o) const {
    return Vector2(this->x * o, this->y * o);
}

Pancake::Math::Vector2 Pancake::Math::Vector2::operator/(const float& o) const {
    return Vector2(this->x / o, this->y / o);
}

std::ostream& Pancake::Math::operator<<(std::ostream& stream, const Pancake::Math::Vector2& v) {
    stream << '(' << v.x << ',' << v.y << ')';
    return stream;
}

void Pancake::Math::Vector2::add(const Pancake::Math::Vector2& o) {
    x += o.x;
    y += o.y;
}

void Pancake::Math::Vector2::subtract(const Pancake::Math::Vector2& o) {
    x -= o.x;
    y -= o.y;
}

void Pancake::Math::Vector2::multiply(const Pancake::Math::Vector2& o) {
    x *= o.x;
    y *= o.y;
}

void Pancake::Math::Vector2::divide(const Pancake::Math::Vector2& o) {
    x /= o.x;
    y /= o.y;
}

void Pancake::Math::Vector2::add(float o) {
    x += o;
    y += o;
}

void Pancake::Math::Vector2::subtract(float o) {
    x -= o;
    y -= o;
}

void Pancake::Math::Vector2::multiply(float o) {
    x *= o;
    y *= o;
}

void Pancake::Math::Vector2::divide(float o) {
    x /= o;
    y /= o;
}

void Pancake::Math::Vector2::invert() {
    multiply(-1);
}

float Pancake::Math::Vector2::dot(const Pancake::Math::Vector2& o) const {
    return ((this->x * o.y) - (o.x * this->y));
}

void Pancake::Math::Vector2::normalize() {
    double l = length();
    x /= l;
    y /= l;
}

Pancake::Math::Vector2 Pancake::Math::Vector2::normalized() {
    double l = length();
    if (l == 0) {
        return Vector2();
    }
    return Vector2(x /= l, y /= l);
}

double Pancake::Math::Vector2::length() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Pancake::Math::Vector2::rotate(float theta) {
    double cs = cos(theta);
    double sn = sin(theta);

    double px = x * cs - y * sn;
    double py = x * sn + y * cs;

    x = (float) px;
    y = (float) py;
}

float Pancake::Math::Vector2::rad() {
    return (float) atan2(y, x);
}

float Pancake::Math::Vector2::deg() {
    return (float) (atan2(y, x) * (180 / M_PI));
}
