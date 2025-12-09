#include "FallingState.h"
#include "IdleState.h"

void FallingState::enter(std::shared_ptr<Entity>& owner) {

}
std::shared_ptr<State> FallingState::handleInput(std::shared_ptr<Entity>& owner, std::vector<Command>& commands) {
	return nullptr;
}
std::shared_ptr<State> FallingState::update(std::shared_ptr<Entity>& owner, float deltaTime) {
	std::cout << "FAAAAAAAAAAALIIIIIIIIIIIIIIINGGGGGG";
	if (owner->movement->isOnGround) {
		return std::make_shared<IdleState>();
	}
	return nullptr;
}
void FallingState::exit(std::shared_ptr<Entity>& owner) {

}