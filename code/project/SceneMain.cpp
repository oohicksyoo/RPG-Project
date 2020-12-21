//
// Created by Alex on 12/13/2020.
//

#include "SceneMain.hpp"
#include "../engine/core/PerspectiveCamera.hpp"
#include "../engine/core/SDLWrapper.hpp"
#include "../engine/core/LuaWrapper.hpp"
#include "../engine/core/Log.hpp"

#include "Player.hpp"

using RPG::SceneMain;
using RPG::Assets::Pipeline;
using RPG::Assets::StaticMesh;
using RPG::Assets::Texture;

namespace {
	RPG::PerspectiveCamera CreateCamera(const RPG::WindowSize& size) {
		return RPG::PerspectiveCamera(static_cast<float>(size.width), static_cast<float>(size.height));
	}
}

struct SceneMain::Internal {
	RPG::PerspectiveCamera camera;
	std::vector<RPG::StaticMeshInstance> staticMeshes;
	RPG::Player player;
	const uint8_t* keyboardState;

	Internal(const RPG::WindowSize& size) : camera(::CreateCamera(size)),
											player(RPG::Player(glm::vec3{ 0.0f, 0.0f, 2.0f })),
											keyboardState(SDL_GetKeyboardState(nullptr)) {}

	RPG::AssetManifest GetAssetManifest() {
		return RPG::AssetManifest{
				{Pipeline::Default},
				{StaticMesh::Crate},
				{Texture::Crate}
		};
	}

	void Prepare() {

		staticMeshes.push_back(RPG::StaticMeshInstance{
				StaticMesh::Crate,
				Texture::Crate,
				glm::vec3{0.0f, 0.0f, 0.0f},
				glm::vec3{0.4f, 0.4f, 0.4f},
				glm::vec3{0.0f, 0.4f, 0.9f},
				0.0f
		});

		//Calling Lua functions
		{
			const char* LUA_FILE = R"(
            function Pythagoras(a, b)
                return (a * a) + (b * b), a, b
            end
            )";
			lua_State* L = luaL_newstate();
			luaL_dostring(L, LUA_FILE);
			lua_getglobal(L, "Pythagoras");
			if (lua_isfunction(L, -1)) {
				lua_pushnumber(L, 3);
				lua_pushnumber(L, 4);
				//Stack, Param Amount, Returns, Error Handling
				lua_pcall(L, 2, 3, 0);
				std::string s = "Value = " + std::to_string((int)lua_tonumber(L, -3));
				RPG::Log("Lua", s);
			}
			lua_close(L);
		}

		lua_State* L = luaL_newstate();
		luaL_dostring(L, "x = 42");
		lua_getglobal(L, "x");
		lua_Number x = lua_tonumber(L, 1);
		std::string s = "Value = " + std::to_string((int)x);
		RPG::Log("Lua", s);
		lua_close(L);

		//Calling Native functions
		{
			//Lambda in c++
			auto NativePythagoras = [](lua_State* L) -> int {
				lua_Number a = lua_tonumber(L, -2);
				lua_Number b = lua_tonumber(L, -1);
				lua_Number csqr = (a * a) + (b * b);
				lua_pushnumber(L, csqr);
				return 1;
			};

			const char* LUA_FILE = R"(
            function Pythagoras(a, b)
                csqr = NativePythagoras(a, b)
                return csqr, a, b
            end
            )";
			lua_State* L = luaL_newstate();
			lua_pushcfunction(L, NativePythagoras);
			lua_setglobal(L, "NativePythagoras");
			luaL_dostring(L, LUA_FILE);
			lua_getglobal(L, "Pythagoras");
			if (lua_isfunction(L, -1)) {
				lua_pushnumber(L, 3);
				lua_pushnumber(L, 4);
				//Stack, Param Amount, Returns, Error Handling
				lua_pcall(L, 2, 3, 0);
				std::string s = "Value = " + std::to_string((int)lua_tonumber(L, -3));
				RPG::Log("Lua", s);
			}
			lua_close(L);
		}

		//Using Native Types in Lua
		{
			struct Sprite {
				int x;
				int y;

				void Move(int velX, int velY) {
					x += velX;
					y += velY;
				}
			};

			auto CreateSprite = [](lua_State* L) -> int {
				Sprite* sprite = (Sprite*)lua_newuserdata(L, sizeof(Sprite));
				sprite->x = 0;
				sprite->y = 0;
				return 1;
			};

			auto MoveSprite = [](lua_State* L) -> int {
				Sprite* sprite = (Sprite*)lua_touserdata(L, -3);
				int velX = (int)lua_tonumber(L, -2);
				int velY = (int)lua_tonumber(L, -1);
				sprite->Move(velX, velY);
				return 0;
			};

			const char* LUA_FILE = R"(
            sprite = CreateSprite()
            MoveSprite(sprite, 5, 7)
            )";
			lua_State* L = luaL_newstate();
			lua_pushcfunction(L, CreateSprite);
			lua_setglobal(L, "CreateSprite");
			lua_pushcfunction(L, MoveSprite);
			lua_setglobal(L, "MoveSprite");
			luaL_dostring(L, LUA_FILE);
			lua_getglobal(L, "sprite");
			if (lua_isuserdata(L, -1)) {
				Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
				std::string s = "x = " + std::to_string(sprite->x) + " y = " + std::to_string(sprite->y);
				RPG::Log("Lua", s);
			}
			lua_close(L);
		}

		//Coroutines
		{
			auto Log = [](lua_State* L) -> int {
				if (lua_gettop(L) != 1) return -1;
				const char* value = lua_tostring(L, -1);
				RPG::Log("Lua", value);
				return 0;
			};

			auto Yield = [](lua_State* L) -> int {
				lua_yield(L, 0);
				return 0;
			};

			const char* LUA_FILE = R"(
            local co
            function OnBehaviour()
                Log("Starting OnBehaviour")
                co = coroutine.create(SampleCoroutine)
            end
            function SampleCoroutine()
                Log("Hello")
                coroutine.yield()
                Log("World")
            end
            function Resume()
                coroutine.resume(co)
            end
            )";
			lua_State* L = luaL_newstate();
			luaL_openlibs(L);
			lua_pushcfunction(L, Log);
			lua_setglobal(L, "Log");
			lua_pushcfunction(L, Yield);
			lua_setglobal(L, "Yield");
			int result = luaL_dostring(L, LUA_FILE);
			RPG::Log("Lua", std::to_string(lua_gettop(L)));

			if (result != LUA_OK) {
				RPG::Log("Lua", lua_tostring(L, -1));
			} else {
				//lua_State* thread = lua_newthread(L);
				lua_getglobal(L, "OnBehaviour");
				lua_pcall(L, 0, 0, 0);
				lua_getglobal(L, "Resume");
				lua_pcall(L, 0, 0, 0);
				lua_getglobal(L, "Resume");
				lua_pcall(L, 0, 0, 0);
				/*if (lua_isfunction(thread, -1)) {
					lua_pcall(thread, 0, 0, 0);
					//rpg::log("Lua", std::to_string(lua_gettop(L)));
					rpg::log("Lua", lua_typename(thread, lua_type(thread, -1)));
					if (lua_isstring(thread, -1)) {
						rpg::log("Lua", lua_tostring(thread, -1));
					} else {
						lua_State* from = lua_tothread(thread, -1);
						//rpg::log("Lua", std::to_string(lua_status(thread)));


						int r = lua_resume(thread, from, 0);
						if (r == LUA_YIELD) {
							rpg::log("Lua", "Yield");
						} else if (r == LUA_OK) {
							rpg::log("Lua", "Okay");
						} else {
							if (lua_isstring(thread, -1)) {
								rpg::log("Lua", lua_tostring(thread, -1));
							}
						}
					}
				}*/
			}

			lua_close(L);
		}
	}

	void Update(const float& delta) {
		ProcessInput(delta);

		camera.Configure(player.GetPosition(), player.GetDirection());

		const glm::mat4 cameraMatrix{camera.GetProjectionMatrix() * camera.GetViewMatrix()};

		for (auto& staticMesh : staticMeshes) {
			staticMesh.RotateBy(delta * 45.0f);
			staticMesh.Update(cameraMatrix);
		}
	}

	void Render(RPG::Renderer& renderer) {
		renderer.Render(Pipeline::Default, staticMeshes);
	}

	void OnWindowResized(const RPG::WindowSize& size) {
		camera = ::CreateCamera(size);
	}

	void ProcessInput(const float& delta) {
		if (keyboardState[SDL_SCANCODE_UP]) {
			player.MoveForward(delta);
		}

		if (keyboardState[SDL_SCANCODE_DOWN]) {
			player.MoveBackward(delta);
		}

		if (keyboardState[SDL_SCANCODE_A]) {
			player.MoveUp(delta);
		}

		if (keyboardState[SDL_SCANCODE_Z]) {
			player.MoveDown(delta);
		}

		if (keyboardState[SDL_SCANCODE_LEFT]) {
			player.TurnLeft(delta);
		}

		if (keyboardState[SDL_SCANCODE_RIGHT]) {
			player.TurnRight(delta);
		}
	}
};

SceneMain::SceneMain(const RPG::WindowSize& size) : internal(RPG::MakeInternalPointer<Internal>(size)) {}

RPG::AssetManifest SceneMain::GetAssetManifest() {
	return internal->GetAssetManifest();
}

void SceneMain::Prepare() {
	internal->Prepare();
}

void SceneMain::Update(const float& delta) {
	internal->Update(delta);
}

void SceneMain::Render(RPG::Renderer& renderer) {
	internal->Render(renderer);
}

void SceneMain::OnWindowResized(const RPG::WindowSize& size) {
	internal->OnWindowResized(size);
}