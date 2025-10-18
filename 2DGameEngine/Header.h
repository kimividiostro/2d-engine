#pragma once
#include"Vec2.h"
#include"SFML/Graphics.hpp"

struct CTransform {
	Vec2 position = { 1,1 };
	Vec2 scale = { 1,1 };
	Vec2 velocity = { 0,0 };
	float rotation = 0; // in degrees

	CTransform(Vec2& p, Vec2& s, Vec2& v, float r) : position(p), scale(s), velocity(v), rotation(r) {}
};

struct CShape {
	sf::CircleShape shape;
	CShape(float radius, int pointCount, sf::Color& color) : shape(radius, pointCount) {
		shape.setFillColor(color);
	}
};

