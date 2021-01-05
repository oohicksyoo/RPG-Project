//
// Created by Alex on 12/13/2020.
//

#pragma once

#include "../engine/core/InternalPointer.hpp"
#include "../engine/core/WindowSize.hpp"
#include "../engine/core/IScene.hpp"
#include "../engine/core/FrameBuffer.hpp"
#include "../engine/core/Hierarchy.hpp"

namespace RPG {
	struct SceneMain : public RPG::IScene {
		public:
			SceneMain(const RPG::WindowSize& frameSize);
			RPG::AssetManifest GetAssetManifest() override;
			void Prepare() override;
			void Awake() override;
			void Start() override;
			void Update(const float& delta) override;
			void Render(RPG::IRenderer& renderer) override;
			void RenderToFrameBuffer(RPG::IRenderer& renderer, std::shared_ptr<RPG::FrameBuffer> frameBuffer) override;
			void OnWindowResized(const RPG::WindowSize& size) override;
			std::shared_ptr<RPG::Hierarchy> GetHierarchy() override;

		private:
			struct Internal;
			RPG::InternalPointer<Internal> internal;
	};
}


