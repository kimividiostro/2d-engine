#include "Game.h"
#include <iostream>
#include "CollisionSystem.h"
#include "NumberGeneratorSystem.h"

Game::Game() {
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight), "My Game");
	m_window.setFramerateLimit(m_fps);
	m_inputState = InputState();

	auto player = m_entityManager.CreateEntity(PLAYER);
	player->transform = std::make_shared<CTransform>(Vec2(m_screenWidth / 2, m_screenHeight / 2), Vec2(0, 0), 0);
	player->shape = std::make_shared<CShape>(30, 30, sf::Color::Green, sf::Color::White, 2.0f);
	player->boundingBox = std::make_shared<CBoundingBox>(30, 30);
	//spawnEnemy();
	createMap();
}

void Game::run()
{
	while (m_window.isOpen())
	{
		processInput();
		m_entityManager.Update();
		if (m_inputState.shoot)
		{
			std::shared_ptr<Entity> projectile = nullptr;
			auto playerPosition = m_entityManager.GetEntitiesByType(PLAYER)[0]->transform->position;
			if (m_entityManager.GetEntitiesByType(PROJECTILE).size() == 0) {
				projectile = m_entityManager.CreateEntity(PROJECTILE);
				auto mousePos = sf::Mouse::getPosition(m_window);
				Vec2 target = Vec2(mousePos.x, mousePos.y);
				auto bulletPath = (target - playerPosition).normalize() * 10.0f;
				projectile->shape = std::make_shared<CShape>(5, 5, sf::Color::Yellow, sf::Color::White, 1.0f);
				projectile->boundingBox = std::make_shared<CBoundingBox>(5, 5);
				projectile->transform = std::make_shared<CTransform>(playerPosition, bulletPath, 0);
			}
			else {
				projectile = m_entityManager.GetEntitiesByType(PROJECTILE)[0];
			}
		}

		for (auto entity : m_entityManager.GetAllEntities()) {
			if (entity->transform) {
				// Player movement based on input
				if (entity->getType() == PLAYER) {
					entity->transform->velocity = { 0,0 };
					if (m_inputState.up) entity->transform->velocity.y = -5;
					if (m_inputState.down) entity->transform->velocity.y = 5;
					if (m_inputState.left) entity->transform->velocity.x = -5;
					if (m_inputState.right) entity->transform->velocity.x = 5;
				}

				// Update entity positions based on their velocity
				entity->transform->previousPosition = entity->transform->position;
				entity->transform->position += entity->transform->velocity;

				if (entity->getType() != PLAYER) {
					auto player = m_entityManager.GetEntitiesByType(PLAYER)[0];
					auto collisionInfo = CollisionSystem::CheckEntityCollision(player, entity);
					if (collisionInfo.collided) {
						CollisionSystem::ResolveCollision(player, collisionInfo);
					}
				}

				if (entity->getType() == PLAYER) {
					std::cout << "Transform XY: { " << entity->transform->position.x << ", " << entity->transform->position.y << std::endl;

					std::cout << "Shape XY: { " << entity->shape->shape.getPosition().x << ", " << entity->shape->shape.getPosition().y << std::endl;
				}

				if (!CollisionSystem::InBoundsOfWindow(m_screenWidth, m_screenHeight, entity)) {
					if (entity->getType() == PROJECTILE) {
						m_entityManager.RemoveEntity(entity);
					}
					if (entity->getType() == ENEMY) {
						entity->transform->velocity *= -1;
					}
					CollisionSystem::ResetEntityPositionInsideWindow(m_screenWidth, m_screenHeight, entity);
				}
			}


			// Rotate shape
			if (entity->rotation)
			{
				entity->transform->angle += entity->rotation->rotationSpeed;
				entity->shape->shape.setRotation(entity->transform->angle);
			}

			// Collision detection between projectiles and enemies
			if (entity->getType() == PROJECTILE) {
				for (auto e : m_entityManager.GetAllEntities()) {
					if(CollisionSystem::CheckEntityCollision(e, entity).collided) {
						if(e->getType() == ENEMY) {
							m_entityManager.RemoveEntity(e);
							m_entityManager.RemoveEntity(entity);
							m_inputState.shoot = false;
							spawnEnemy();
							break;
						}
						if (e->getType() == WALL || e->getType() == FLOOR) {
							m_entityManager.RemoveEntity(entity);
							m_inputState.shoot = false;
							break;
						}
					}
				}
			}
		}
		render();
	}

}

void Game::render() {
	m_window.clear();
	for (auto entity : m_entityManager.GetAllEntities()) {
		// Update SFML shape position
		if (entity->transform && entity->shape) {
			entity->shape->shape.setPosition(entity->transform->position.x, entity->transform->position.y);
			m_window.draw(entity->shape->shape);
		}
	}
	m_window.display();
}

void Game::processInput() {
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) m_inputState.up = true;
			if (event.key.code == sf::Keyboard::Down) m_inputState.down = true;
			if (event.key.code == sf::Keyboard::Left) m_inputState.left = true;
			if (event.key.code == sf::Keyboard::Right) m_inputState.right = true;
			if (event.key.code == sf::Keyboard::Space) m_inputState.action = true;
			
			std::cout << "Up pressed: " << m_inputState.up << ", Down pressed: " << m_inputState.down
				<< ", Left pressed: " << m_inputState.left << ", Right pressed: " << m_inputState.right
				<< ", Action pressed: " << m_inputState.action << std::endl;
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Up) m_inputState.up = false;
			if (event.key.code == sf::Keyboard::Down) m_inputState.down = false;
			if (event.key.code == sf::Keyboard::Left) m_inputState.left = false;
			if (event.key.code == sf::Keyboard::Right) m_inputState.right = false;
			if (event.key.code == sf::Keyboard::Space) m_inputState.action = false;
			std::cout << "Up pressed: " << m_inputState.up << ", Down pressed: " << m_inputState.down
				<< ", Left pressed: " << m_inputState.left << ", Right pressed: " << m_inputState.right
				<< ", Action pressed: " << m_inputState.action << std::endl;
		}

		if(event.type == sf::Event::MouseButtonPressed) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Left mouse button pressed at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
				m_inputState.shoot = true;
			}
		}

		if(event.type == sf::Event::MouseButtonReleased) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Left mouse button released at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
				m_inputState.shoot = false;
			}
		}
	}
}

void Game::spawnEnemy() {
	auto enemy = m_entityManager.CreateEntity(ENEMY);
	enemy->shape = std::make_shared<CShape>(20, 20, sf::Color::Red, sf::Color::White, 2.0f);
	auto position = NumberGeneratorSystem::GenerateEntityPositionInsideWindow(m_screenWidth, m_screenHeight, enemy);
	enemy->transform = std::make_shared<CTransform>(position, Vec2(0, 0), 0);
	enemy->boundingBox = std::make_shared<CBoundingBox>(20, 20);
}

void Game::createMap() {
	auto floor = m_entityManager.CreateEntity(FLOOR);
	floor->shape = std::make_shared<CShape>(800, 100, sf::Color::Magenta, sf::Color::White, 2.0f);
	floor->transform = std::make_shared<CTransform>(Vec2(400, 500), Vec2(0,0), 0);
	floor->boundingBox = std::make_shared<CBoundingBox>(800, 100);
	auto wall = m_entityManager.CreateEntity(WALL);
	wall->shape = std::make_shared<CShape>(50, 200, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall->transform = std::make_shared<CTransform>(Vec2(600, 350), Vec2(0, 0), 0);
	wall->boundingBox = std::make_shared<CBoundingBox>(50, 200);
}