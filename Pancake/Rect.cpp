//

#include "Rect.h"

//
// Created by Michael Malura on 24/04/17.
Pancake::Math::Rect::Rect() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Pancake::Math::Rect::Rect(Pancake::Math::Vector2 position, Pancake::Math::Vector2 size) {
    this->x = position.x;
    this->y = position.y;
    this->w = size.x;
    this->h = size.y;
}

Pancake::Math::Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Pancake::Math::Rect::expand(float v) {
    x -= v;
    y -= v;
    w += (v * 2);
    h += (v * 2);
}

void Pancake::Math::Rect::shrink(float v) {
    expand(-v);
}

float Pancake::Math::Rect::getLeft() {
    return x;
}

float Pancake::Math::Rect::getRight() {
    return x + w;
}

float Pancake::Math::Rect::getTop() {
    return y;
}

float Pancake::Math::Rect::getBottom() {
    return y + h;
}

float Pancake::Math::Rect::getX() {
    return x;
}

float Pancake::Math::Rect::getY() {
    return y;
}

float Pancake::Math::Rect::getWidth() {
    return w;
}

float Pancake::Math::Rect::getHeight() {
    return h;
}

bool Pancake::Math::Rect::isInside(Pancake::Math::Vector2 point) {
    return getLeft() <= point.x && getRight() >= point.x &&
           getTop() <= point.y && getBottom() >= point.y;
}

bool Pancake::Math::Rect::isOutside(Pancake::Math::Vector2 point) {
    return !isInside(point);
}

void Pancake::Math::Rect::setX(float x) {
    this->x = x;
}

void Pancake::Math::Rect::setY(float y) {
    this->y = y;
}

void Pancake::Math::Rect::setWidth(float w) {
    this->w = w;
}

void Pancake::Math::Rect::setHeight(float h) {
    this->h = h;
}

void Pancake::Math::Rect::setPosition(Vector2 position) {
    setX(position.x);
    setY(position.y);
}

void Pancake::Math::Rect::setSize(Vector2 size) {
    setWidth(size.x);
    setHeight(size.y);
}

Pancake::Math::Vector2 Pancake::Math::Rect::getPosition() {
    return Pancake::Math::Vector2(x, y);
}

Pancake::Math::Vector2 Pancake::Math::Rect::getSize() {
    return Pancake::Math::Vector2(w, h);
}
