//
// Created by Alex on 12/13/2020.
//

#pragma once

#include "../engine/core/GLMWrapper.hpp"
#include "../engine/core/InternalPointer.hpp"

namespace RPG {
	struct Player {
		public:
			Player(const glm::vec3& position);
			void MoveForward(const float& delta);
			void MoveBackward(const float& delta);
			void MoveUp(const float& delta);
			void MoveDown(const float& delta);
			void TurnLeft(const float& delta);
			void TurnRight(const float& delta);
			glm::vec3 GetPosition() const;
			glm::vec3 GetDirection() const;

		private:
			struct Internal;
			RPG::InternalPointer<Internal> internal;
	};
}


