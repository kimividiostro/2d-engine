#pragma once
#include "Vec2.h"

Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

bool Vec2::operator == (const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator != (const Vec2& rhs) const {
	return x != rhs.x || y != rhs.y;
}

bool Vec2::operator > (const Vec2& rhs) const {
	return x > rhs.x || ((int)x == (int)rhs.x && y > rhs.y);
}

bool Vec2::operator < (const Vec2& rhs) const {
	return x < rhs.x || ((int) x == (int) rhs.x && y < rhs.y);
}


Vec2 Vec2::operator + (const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float scalar) const {
	return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator / (const float scalar) const {
	return Vec2(x / scalar, y / scalar);
}

Vec2 Vec2::operator += (const Vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2 Vec2::operator -= (const Vec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2 Vec2::operator *= (const float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vec2 Vec2::operator /= (const float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

float Vec2::length() const {
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize() const {
	float len = length();
	return Vec2(x / len, y / len);
}

float Vec2::distance(const Vec2& rhs) const {
	return (*this - rhs).length();
}

float Vec2::dot(const Vec2& vec2) const {
	return x * vec2.x + y * vec2.y;
}

std::string Vec2::toString() const {
	return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}