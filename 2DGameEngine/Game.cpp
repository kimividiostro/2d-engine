#include "Game.h"
#include <iostream>
#include "CollisionSystem.h"
#include "NumberGeneratorSystem.h"
#include "IdleState.h"

Game::Game() {
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight), "My Game");
	m_window.setFramerateLimit(m_fps);

	m_inputManager.registerCommand(sf::Keyboard::Left, MOVE_LEFT);
	m_inputManager.registerCommand(sf::Keyboard::Right, MOVE_RIGHT);
	m_inputManager.registerCommand(sf::Keyboard::Up, JUMP);
	m_inputManager.registerCommand(sf::Keyboard::Space, SHOOT);

	m_inputManager.setCommandState(MOVE_LEFT, false);
	m_inputManager.setCommandState(MOVE_RIGHT, false);
	m_inputManager.setCommandState(JUMP, false);
	m_inputManager.setCommandState(SHOOT, false);

	EntityID playerId = 1;
	
	m_world.add<Transform>(playerId);
	auto& transform = m_world.get<Transform>(playerId);
	transform.position = Vec2(m_screenWidth / 2, m_screenHeight / 2);
	
	m_world.add<Render>(playerId);
	auto& renderComp = m_world.get<Render>(playerId);
	renderComp.sfShape.setPosition(transform.position.x,transform.position.y);
	renderComp.sfShape.setSize(sf::Vector2f(50, 50));
	renderComp.sfShape.setFillColor(sf::Color::Green);
	renderComp.sfShape.setOrigin(25, 25); // Center the origin

	auto player = m_world.m_entityManager.CreateEntity(PLAYER);
	player->transform = new CTransform(Vec2(m_screenWidth / 2, m_screenHeight / 2));
	player->shape = new CShape(30, 30, sf::Color::Green, sf::Color::White, 2.0f);
	player->boundingBox = new CBoundingBox(30, 30);
	// TODO: Fix magic numbers
	player->movement = new CMovement(
		Vec2(0, 0), // velocity
		150, // max speed
		50, // acceleration
		400, // friction
		0,  // direction -1, 0, 1
		-400, // jump veolicty
		250); // gravity
	player->state = new IdleState();
	//spawnEnemy();
	createMap();
}

void Game::run()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		processInput();
		m_world.m_entityManager.Update();
		m_world.m_movementSystem.update(deltaTime);
		m_world.m_collisionSystem.update(deltaTime);
		m_renderingSystem.update(deltaTime);
	}

}

void Game::processInput() {
	sf::Event event;

	m_inputManager.clearCommands();
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
			
		auto commandName = m_inputManager.getCommandNameByKey(event.key.code);
		if (commandName == 0) {
			continue;
		}

		if (event.type == sf::Event::KeyPressed) {
			m_inputManager.addCommand(START, commandName);
			m_inputManager.setCommandState(commandName, true);
		}

		if (event.type == sf::Event::KeyReleased) {
			m_inputManager.addCommand(END, commandName);
			m_inputManager.setCommandState(commandName, false);
		}
	}
}

void Game::spawnEnemy() {
	auto enemy = m_world.m_entityManager.CreateEntity(ENEMY);
	enemy->shape = new CShape(20, 20, sf::Color::Red, sf::Color::White, 2.0f);
	auto position = NumberGeneratorSystem::GenerateEntityPositionInsideWindow(m_screenWidth, m_screenHeight, *enemy);
	enemy->transform = new CTransform(position);
	enemy->boundingBox = new CBoundingBox(20, 20);
}

void Game::createMap() {
	auto floor = m_world.m_entityManager.CreateEntity(FLOOR);
	floor->shape = new CShape(800, 100, sf::Color::Magenta, sf::Color::White, 2.0f);
	floor->transform = new CTransform(Vec2(400, 500));
	floor->boundingBox = new CBoundingBox(800, 100);

	auto wall1 = m_world.m_entityManager.CreateEntity(WALL);
	wall1->shape = new CShape(50, 150, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall1->transform = new CTransform(Vec2(600, 400));
	wall1->boundingBox = new CBoundingBox(50, 150);

	auto wall2 = m_world.m_entityManager.CreateEntity(WALL);
	wall2->shape = new CShape(50, 100, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall2->transform = new CTransform(Vec2(500, 400));
	wall2->boundingBox = new CBoundingBox(50, 100);

	auto wall3 = m_world.m_entityManager.CreateEntity(WALL);
	wall3->shape = new CShape(50, 50, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall3->transform = new CTransform(Vec2(400, 450));
	wall3->boundingBox = new CBoundingBox(50, 50);

	auto wall4 = m_world.m_entityManager.CreateEntity(WALL);
	wall3->shape = new CShape(50, 50, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall3->transform = new CTransform(Vec2(400, 300));
	wall3->boundingBox = new CBoundingBox(50, 50);
}