#pragma once
#include <string>

class Vec2 {
public:
	float x, y = 0;
	
	Vec2();
	Vec2(float x, float y);
	
	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;
	bool operator < (const Vec2& rhs) const;
	bool operator > (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const float scalar) const;
	Vec2 operator / (const float scalar) const;

	Vec2 operator += (const Vec2& rhs);
	Vec2 operator -= (const Vec2& rhs);
	Vec2 operator *= (const float scalar);
	Vec2 operator /= (const float scalar);

	float length() const;
	Vec2 normalize() const;
	float distance(const Vec2& rhs) const;

	std::string toString() const;
};