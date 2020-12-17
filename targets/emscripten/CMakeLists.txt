cmake_minimum_required(VERSION 3.4.1)

# We are using C++ 17 and will make use of C++ exceptions.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

set(THIRD_PARTY_DIR "../../third-party")
set(MAIN_SOURCE_DIR "../../code")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

include_directories(${THIRD_PARTY_DIR}/SDL/include)
include_directories(${THIRD_PARTY_DIR}/glm)
include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)
include_directories(${THIRD_PARTY_DIR}/SDL2_image)
include_directories(${THIRD_PARTY_DIR}/lua)

#Fill this out correctly
file(GLOB ALL_CPP_SOURCES
	${MAIN_SOURCE_DIR}/*.cpp
	${MAIN_SOURCE_DIR}/engine/application/*.hpp
	${MAIN_SOURCE_DIR}/engine/application/*.cpp
	${MAIN_SOURCE_DIR}/engine/application/opengl/*.hpp
	${MAIN_SOURCE_DIR}/engine/application/opengl/*.cpp
	${MAIN_SOURCE_DIR}/engine/core/*.hpp
	${MAIN_SOURCE_DIR}/engine/core/*.cpp
	${MAIN_SOURCE_DIR}/project/*.hpp
	${MAIN_SOURCE_DIR}/project/*.cpp
)
file(GLOB_RECURSE C_HEADERS ${THIRD_PARTY_DIR}/lua/*.h)
file(GLOB_RECURSE C_SOURCES ${THIRD_PARTY_DIR}/lua/*.c)

set(LUA_C_FILES ${C_SOURCES})
list(REMOVE_ITEM LUA_C_FILES ${THIRD_PARTY_DIR}/lua/lua.c)

# The 'rpg-engine' executable is the output target for our Emscripten application and is why we end up with 'a-simple-triangle.js' in the output folder. Note that it will use the C++ source code from the shared 'main' folder through the collated sources.
add_executable(
	rpg-engine
	${ALL_CPP_SOURCES}
	${C_HEADERS}
	${LUA_C_FILES}
)

# These properties specify what kind of Emscripten build to perform and are assigned to our 'a-simple-triangle' executable target.
set_target_properties(
	rpg-engine
	PROPERTIES
	LINK_FLAGS
	"-O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"['png']\" -s USE_WEBGL2=1 --preload-file ../../../assets@/assets"
)

# When the build is complete we will run the 'cmake-post-build.sh' script.
add_custom_command(
	TARGET rpg-engine
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ./cmake-post-build.sh
)