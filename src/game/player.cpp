#include "player.h"
#include "scene.h"
#include "rendercomponent.h"

//TODO: Find more elegant solution for this
static bool pressed[4];
const size_t Player::MAX_CARRY_AMOUNT = 10;

void Player::init() {
	prevPosition = *getTransform()->getPosition();

	parent->addComponent((new RenderComponent(
			parent->getScene()->getMesh("Person.obj"),
			new Material(parent->getScene()->getVideoDriver()->getTexture("solis.png")))));
}

void Player::input(float, SolisDevice *device) {
	if (device->keyPressed(GLFW_KEY_I)) {
		if (!pressed[0] && getTransform()->getPosition()->z < 31) {
			getTransform()->moveForward(-1.0);
			pressed[0] = true;
		}
	} else {
		pressed[0] = false;
	}
	if (device->keyPressed(GLFW_KEY_J)) {
		if (!pressed[1] && getTransform()->getPosition()->x < 31) {
			getTransform()->moveRight(1.0);
			pressed[1] = true;
		}
	} else {
		pressed[1] = false;
	}
	if (device->keyPressed(GLFW_KEY_K)) {
		if (!pressed[2] && getTransform()->getPosition()->z > 0) {
			getTransform()->moveForward(1.0);
			pressed[2] = true;
		}
	} else {
		pressed[2] = false;
	}
	if (device->keyPressed(GLFW_KEY_L)) {
		if (!pressed[3] && getTransform()->getPosition()->x > 0) {
			getTransform()->moveRight(-1.0);
			pressed[3] = true;
		}
	} else {
		pressed[3] = false;
	}

	if (device->keyPressed(GLFW_KEY_M) && carrying >= 8) {
		auto pos = getTransform()->getPosition();
		if (field->build(BuildingType::eSawmill, pos->x, pos->z + 1)) {
			carrying -= 8;
		}
		
	}
}

void Player::update(float) {
	auto pos = *getTransform()->getPosition();
	if(pos != prevPosition) {
		if((int)pos.x >= 32 || (int)pos.y >= 32) {
			getTransform()->setPosition(prevPosition);
			return;
		}

		auto block = field->blocks.at((int)pos.x).at((int)pos.z);
		if(block->getType() == BlockType::eTree) {
			auto tree = static_cast<Tree *>(block->getContent().get());
			carrying += tree->chopWood(2);
			if (!tree->getWoodAmount()) {
				field->removeBlock((int)pos.x, (int)pos.z);
				prevPosition = *getTransform()->getPosition();
			} else {
				getTransform()->setPosition(prevPosition);
			}
		} else if(block->getType() == BlockType::eEmpty) {
			prevPosition = *getTransform()->getPosition();
		} else {
			getTransform()->setPosition(prevPosition);
		}
	}

}