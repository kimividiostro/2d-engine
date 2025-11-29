#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

struct CTransform {
	Vec2 position;
	Vec2 previousPosition;
	Vec2 velocity;
	int angle = 0;
	CTransform(const Vec2& position, const Vec2& velocity, int angle) : position(position), velocity(velocity), angle(angle)
	{}
};

struct CShape {
	sf::RectangleShape shape;

	CShape(int width, int height, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) {
		shape.setSize(sf::Vector2f(width,height));
		shape.setFillColor(fillColor);
		//shape.setOutlineColor(outlineColor);
		//shape.setOutlineThickness(outlineThickness);
		shape.setOrigin(width/2, height/2); // Center the origin
	}
};

struct CScore {
	int score = 0;
	CScore(int score) : score(score) {}
};

struct CRotation {
	int rotationSpeed = 0; // Degrees per update
	CRotation(int rotationSpeed) : rotationSpeed(rotationSpeed) {}
};

struct CBoundingBox {
	int width, height, halfWidth, halfHeight;

	CBoundingBox(int width, int height) : width(width), height(height), halfWidth(width / 2), halfHeight(height / 2) {}
};

struct CPhysics {
	float mass = 0.0f;
	CPhysics(float mass) : mass(mass) {}
};