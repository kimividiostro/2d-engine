#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"


struct Transform {
	Transform() {}
	Vec2 position;
	float scale = 1.0f;
};

struct Movement {
	Vec2 velocity;
};

struct JumpRequest {};

struct JumpComponent {
	float jumpVelocity;
};

struct Render {
	Render() {}
	sf::RectangleShape sfShape;
};

struct BoundingBox {
	int width, height;
};



struct CTransform {
	Vec2 position;
	Vec2 previousPosition;
	CTransform(const Vec2& position) : position(position) 
	{}
};

struct CShape {
	sf::RectangleShape shape;

	CShape(int width, int height, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) {
		shape.setSize(sf::Vector2f(width,height));
		shape.setFillColor(fillColor);
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

struct CMovement {
	Vec2 velocity;
	float maxSpeed;
	float acceleration;
	float friction;
	short direction;
	float jumpVelocity;
	float gravity;
	bool isOnGround = false;

	// Jump buffering
	float jumpBufferTime = 0.2f;
	float jumpBufferTimer = 0.0f;
	float jumpRequested = false;

	CMovement(Vec2 velocity, float maxSpeed = 0, float acceleration = 0, float friction = 0, short direction = 0, float jumpVelocity = 0, float gravity = 0) 
		: velocity(velocity), maxSpeed(maxSpeed), acceleration(acceleration), friction(friction), direction(direction), jumpVelocity(jumpVelocity), gravity(gravity) { }
};
