#include "Game.h"
#include <iostream>
#include "CollisionSystem.h"
#include "NumberGeneratorSystem.h"
#include "IdleState.h"

Game::Game() {
	m_window.create(sf::VideoMode(m_screenWidth, m_screenHeight), "My Game");
	m_window.setFramerateLimit(m_fps);
	
	m_inputMap[sf::Keyboard::Left] = MOVE_LEFT;
	m_inputMap[sf::Keyboard::Right] = MOVE_RIGHT;
	m_inputMap[sf::Keyboard::Space] = JUMP;
	m_inputMap[sf::Mouse::Left] = SHOOT;

	m_inputState = InputState();

	auto player = m_entityManager.CreateEntity(PLAYER);
	player->transform = new CTransform(Vec2(m_screenWidth / 2, m_screenHeight / 2));
	player->shape = new CShape(30, 30, sf::Color::Green, sf::Color::White, 2.0f);
	player->boundingBox = new CBoundingBox(30, 30);
	// TODO: Fix magic numbers
	player->movement = new CMovement(Vec2(0, 0), 150, 50, 30, 0,  -250, 100);
	player->state = new IdleState();
	//spawnEnemy();
	createMap();
}

void Game::run()
{
	sf::Clock clock;
	float gravity = 90.0f;
	while (m_window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		//std::cout << "DeltaTime: " << deltaTime << "ms" << std::endl;
		processInput();
		m_entityManager.Update();
		if (m_inputState.shoot)
		{
			Entity* projectile = nullptr;
			auto playerPosition = m_entityManager.GetEntitiesByType(PLAYER)[0]->transform->position;
			if (m_entityManager.GetEntitiesByType(PROJECTILE).size() == 0) {
				projectile = m_entityManager.CreateEntity(PROJECTILE);
				auto mousePos = sf::Mouse::getPosition(m_window);
				Vec2 target = Vec2(mousePos.x, mousePos.y);
				auto bulletPath = (target - playerPosition).normalize() * 1000.0f;
				projectile->shape = new CShape(5, 5, sf::Color::Yellow, sf::Color::White, 1.0f);
				projectile->boundingBox = new CBoundingBox(5, 5);
				projectile->transform = new CTransform(playerPosition);
				projectile->movement = new CMovement(bulletPath);
			}
			else {
				projectile = m_entityManager.GetEntitiesByType(PROJECTILE)[0];
			}
		}

		for (auto entity : m_entityManager.GetAllEntities()) {
			if (entity->state) {
				auto newState = entity->state->handleInput(*entity, m_commands);
				if (newState) {
					// TODO: add state pooling to reuse states
					entity->state->exit(*entity);
					entity->state = newState;
					entity->state->enter(*entity);
				}
				newState = entity->state->update(*entity, deltaTime);
				if (newState) {
					entity->state->exit(*entity);
					entity->state = newState;
					entity->state->enter(*entity);
				}

			}
			if (entity->transform) {

				if (entity->getType() != PLAYER) {
					auto player = m_entityManager.GetEntitiesByType(PLAYER)[0];
					auto collisionInfo = CollisionSystem::CheckEntityCollision(*player, *entity);
					if (collisionInfo.collided) {
						CollisionSystem::ResolveCollision(*player, collisionInfo);
						if (entity->getType() == FLOOR || (entity->getType() == WALL && collisionInfo.axis == Y_AXIS)) {
							player->movement->velocity.y = 0;
							player->movement->isOnGround = true;
						}
					}
					else if (entity->getType() == FLOOR) {
						player->movement->isOnGround = false;
					}
				}

				if (!CollisionSystem::InBoundsOfWindow(m_screenWidth, m_screenHeight, *entity)) {
					if (entity->getType() == PROJECTILE) {
						m_entityManager.RemoveEntity(entity);
					}
					if (entity->getType() == ENEMY) {
						entity->movement->velocity *= -1;
					}
					CollisionSystem::ResetEntityPositionInsideWindow(m_screenWidth, m_screenHeight, *entity);
				}

				if (entity->movement) {
					auto moveCom = entity->movement;
					entity->transform->previousPosition = entity->transform->position;
					if (moveCom->direction != 0) {
						moveCom->velocity.x += moveCom->acceleration * moveCom->direction;
						std::cout << "V: " << moveCom->velocity.x << std::endl;
						if (fabs(moveCom->velocity.x) > moveCom->maxSpeed) {
							moveCom->velocity.x = moveCom->maxSpeed * moveCom->direction;
						}
					}

					if (!entity->movement->isOnGround) {
						entity->movement->velocity.y += entity->movement->gravity * deltaTime;
					}

					entity->movement->velocity.y += entity->movement->gravity * deltaTime;
					entity->transform->position += entity->movement->velocity * deltaTime;
				}

			}
			// Collision detection between projectiles and enemies
			if (entity->getType() == PROJECTILE) {
				for (auto e : m_entityManager.GetAllEntities()) {
					if(CollisionSystem::CheckEntityCollision(*e, *entity).collided) {
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

	m_commands.clear();
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
			
		auto commandName = m_inputMap[event.key.code];
		if (commandName == 0) {
			continue;
		}

		if (event.type == sf::Event::KeyPressed) {
			Command command(START, commandName);
			m_commands.push_back(command);
		}

		if (event.type == sf::Event::KeyReleased) {
			Command command(END, commandName);
			m_commands.push_back(command);
		}
	}
}

void Game::spawnEnemy() {
	auto enemy = m_entityManager.CreateEntity(ENEMY);
	enemy->shape = new CShape(20, 20, sf::Color::Red, sf::Color::White, 2.0f);
	auto position = NumberGeneratorSystem::GenerateEntityPositionInsideWindow(m_screenWidth, m_screenHeight, *enemy);
	enemy->transform = new CTransform(position);
	enemy->boundingBox = new CBoundingBox(20, 20);
}

void Game::createMap() {
	auto floor = m_entityManager.CreateEntity(FLOOR);
	floor->shape = new CShape(800, 100, sf::Color::Magenta, sf::Color::White, 2.0f);
	floor->transform = new CTransform(Vec2(400, 500));
	floor->boundingBox = new CBoundingBox(800, 100);
	auto wall = m_entityManager.CreateEntity(WALL);
	wall->shape = new CShape(50, 150, sf::Color::Magenta, sf::Color::White, 2.0f);
	wall->transform = new CTransform(Vec2(600, 400));
	wall->boundingBox = new CBoundingBox(50, 150);
}