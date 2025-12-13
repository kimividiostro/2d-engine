#include "FallingState.h"
#include "IdleState.h"

void FallingState::enter(Entity& owner) {

}
State* FallingState::handleInput(Entity& owner, std::vector<Command>& commands) {
	return nullptr;
}
State* FallingState::update(Entity& owner, float deltaTime) {
	std::cout << "FAAAAAAAAAAALIIIIIIIIIIIIIIINGGGGGG";
	if (owner.movement->isOnGround) {
		return new IdleState();
	}
	return nullptr;
}
void FallingState::exit(Entity& owner) {

}