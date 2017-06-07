//

#include "Rect.h"

//

Rect::Rect() {
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}

Rect::Rect(Vector2 position, Vector2 size) {
  this->x = position.x;
  this->y = position.y;
  this->w = size.x;
  this->h = size.y;
}

Rect::Rect(float x, float y, float w, float h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

void Rect::expand(float v) {
  x -= v;
  y -= v;
  w += (v * 2);
  h += (v * 2);
}

void Rect::shrink(float v) {
  expand(-v);
}

float Rect::getLeft() {
  return x;
}

float Rect::getRight() {
  return x + w;
}

float Rect::getTop() {
  return y;
}

float Rect::getBottom() {
  return y + h;
}

float Rect::getX() {
  return x;
}

float Rect::getY() {
  return y;
}

float Rect::getWidth() {
  return w;
}

float Rect::getHeight() {
  return h;
}

bool Rect::isInside(Vector2 point) {
  return getLeft() <= point.x && getRight() >= point.x &&
         getTop() <= point.y && getBottom() >= point.y;
}

bool Rect::isOutside(Vector2 point) {
  return !isInside(point);
}

void Rect::setX(float x) {
  this->x = x;
}

void Rect::setY(float y) {
  this->y = y;
}

void Rect::setWidth(float w) {
  this->w = w;
}

void Rect::setHeight(float h) {
  this->h = h;
}

void Rect::setPosition(Vector2 position) {
  setX(position.x);
  setY(position.y);
}

void Rect::setSize(Vector2 size) {
  setWidth(size.x);
  setHeight(size.y);
}

Vector2 Rect::getPosition() {
  return Vector2(x, y);
}

Vector2 Rect::getSize() {
  return Vector2(w, h);
}
