#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vec2.h"
#include "EntityManager.h"


int main()
{
	EntityManager entityManager;
	auto entity1 = entityManager.CreateEntity("Player", PLAYER);
	auto entity2 = entityManager.CreateEntity("Enemy1", ENEMY);
	auto entity3 = entityManager.CreateEntity("Enemy2", ENEMY);
	auto entity4 = entityManager.CreateEntity("Enemy3", ENEMY);
	auto entity5 = entityManager.CreateEntity("Projectile1", PROJECTILE);
	auto entity6 = entityManager.CreateEntity("Projectile2", PROJECTILE);

	auto entities = entityManager.GetAllEntities();
	for (auto entity : entityManager.m_entitiesToBeAdded) {
		std::cout << "ID: " << entity->getId() << ", Name: " << entity->getName() << ", Type: " << entity->getType() << ", Active: " << entity->isActive() << std::endl;
	}

	std:: cin.get();
	//int screenWidth = 800;
	//int screenHeight = 600;
 //   sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");

 //   while (window.isOpen())
 //   {
 //       sf::Event event;
 //       while (window.pollEvent(event))
 //       {
 //           if (event.type == sf::Event::Closed)
 //               window.close();            
 //       }

 //       window.clear();

	//	//window.draw();

 //       window.display();
 //   }

    return 0;
}