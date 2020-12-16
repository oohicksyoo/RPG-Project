cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")

set(THIRD_PARTY_DIR "../../third-party")
set(MAIN_SOURCE_DIR "../../code")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

include_directories(${THIRD_PARTY_DIR}/SDL/include)
include_directories(${THIRD_PARTY_DIR}/glm)
include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)
include_directories(${THIRD_PARTY_DIR}/SDL2_image)
include_directories(${THIRD_PARTY_DIR}/vulkan-mac/macOS/include)
include_directories(${THIRD_PARTY_DIR}/lua)

set(DYLIB_VULKAN ${CMAKE_CURRENT_SOURCE_DIR}/Frameworks/libvulkan.1.dylib)
set(DYLIB_MOLTEN_VK ${CMAKE_CURRENT_SOURCE_DIR}/Frameworks/libMoltenVK.dylib)

file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE C_HEADERS ${THIRD_PARTY_DIR}/lua/*.h)
file(GLOB_RECURSE C_SOURCES ${THIRD_PARTY_DIR}/lua/*.c)

set(LUA_C_FILES ${C_SOURCES})
list(REMOVE_ITEM LUA_C_FILES ${THIRD_PARTY_DIR}/lua/lua.c)

add_executable(
	rpg-engine-console
	${CPP_HEADERS}
	${CPP_SOURCES}
	${C_HEADERS}
    ${LUA_C_FILES}
)

set_target_properties(
	rpg-engine-console
	PROPERTIES
	LINK_FLAGS
	"-F../Frameworks -framework SDL2 -framework SDL2_image -framework OpenGL"
)

target_link_libraries(
	rpg-engine-console
	${DYLIB_VULKAN}
	${DYLIB_MOLTEN_VK}
)

add_custom_command(
	TARGET rpg-engine-console
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ./cmake-post-build.sh
)