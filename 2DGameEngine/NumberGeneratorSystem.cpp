#include "NumberGeneratorSystem.h"

Vec2 NumberGeneratorSystem::GenerateEntityPositionInsideWindow(int windowWidth, int windowHeight, const Entity& entity) {
	float entityRadius = entity.shape->shape.getSize().x / 2;
	int maxX = int(windowWidth - entityRadius);
	int maxY = int(windowWidth - entityRadius);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib1(entityRadius, maxX);
	int randomX = distrib1(gen);
	std::uniform_int_distribution<> distrib2(entityRadius, maxY);
	int randomY = distrib2(gen);

	return Vec2(randomX, randomY);
}