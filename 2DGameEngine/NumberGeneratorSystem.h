#pragma once
#include "Vec2.h"
#include<iostream>
#include"Entity.h"
#include <random>

static class NumberGeneratorSystem {
public:
	static Vec2 GenerateEntityPositionInsideWindow(int windowHeight, int windowWidth, const Entity& entity);
};