//
// Created by Alex on 12/13/2020.
//

#include "Player.hpp"

using RPG::Player;

namespace {
	glm::mat4 ComputeOrientation(const glm::mat4& identity, const float& rotationDegrees, const glm::vec3& up) {
		return glm::rotate(identity, glm::radians(rotationDegrees), up);
	}

	glm::vec3 ComputeForwardDirection(const glm::mat4& orientation) {
		return glm::normalize(orientation * glm::vec4(0, 0, 1, 0));
	}
}

struct Player::Internal {
	const glm::mat4 identity;
	const glm::vec3 up;
	const float moveSpeed{5.0f};
	const float turnSpeed{120.0f};

	float rotationDegrees;
	glm::vec3 position;
	glm::mat4 orientation;
	glm::vec3 forwardDirection;

	Internal(const glm::vec3& position) : identity(glm::mat4(1)),
										  up(glm::vec3{ 0.0f, 1.0f, 0.0f }),
										  rotationDegrees(0.0f),
										  position(position),
										  orientation(::ComputeOrientation(identity, rotationDegrees, up)),
										  forwardDirection(::ComputeForwardDirection(orientation)) {}

	void MoveForward(const float& delta) {
		position -= forwardDirection * (moveSpeed * delta);
	}

	void MoveBackward(const float& delta) {
		position += forwardDirection * (moveSpeed * delta);
	}

	void TurnLeft(const float& delta) {
		Rotate(turnSpeed * delta);
	}

	void TurnRight(const float& delta) {
		Rotate(-turnSpeed * delta);
	}

	void MoveUp(const float& delta) {
		position.y += (moveSpeed * delta);
	}

	void MoveDown(const float& delta) {
		position.y -= (moveSpeed * delta);
	}

	void Rotate(const float& amount) {
		rotationDegrees += amount;

		if (rotationDegrees > 360.0f) {
			rotationDegrees -= 360.0f;
		} else if (rotationDegrees < 0.0f) {
			rotationDegrees += 360.0f;
		}

		orientation = ::ComputeOrientation(identity, rotationDegrees, up);
		forwardDirection = ::ComputeForwardDirection(orientation);
	}
};

Player::Player(const glm::vec3& position) : internal(RPG::MakeInternalPointer<Internal>(position)) {}

void Player::MoveForward(const float& delta) {
	internal->MoveForward(delta);
}

void Player::MoveBackward(const float& delta) {
	internal->MoveBackward(delta);
}

void Player::TurnLeft(const float& delta) {
	internal->TurnLeft(delta);
}

void Player::TurnRight(const float& delta) {
	internal->TurnRight(delta);
}

glm::vec3 Player::GetPosition() const {
	return internal->position;
}

glm::vec3 Player::GetDirection() const {
	return internal->forwardDirection;
}

void Player::MoveUp(const float& delta) {
	internal->MoveUp(delta);
}

void Player::MoveDown(const float& delta) {
	internal->MoveDown(delta);
}