//
// Created by Alex on 12/13/2020.
//

#pragma once

#include "../engine/core/InternalPointer.hpp"
#include "../engine/core/WindowSize.hpp"
#include "../engine/core/Scene.hpp"

namespace RPG {
	struct SceneMain : public RPG::Scene {
		public:
			SceneMain(const RPG::WindowSize& frameSize);
			RPG::AssetManifest GetAssetManifest() override;
			void Prepare() override;
			void Update(const float& delta) override;
			void Render(RPG::Renderer& renderer) override;
			void OnWindowResized(const RPG::WindowSize& size) override;

		private:
			struct Internal;
			RPG::InternalPointer<Internal> internal;
	};
}


