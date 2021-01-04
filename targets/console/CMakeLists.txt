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
#include_directories(${THIRD_PARTY_DIR}/imgui)

set(DYLIB_VULKAN ${CMAKE_CURRENT_SOURCE_DIR}/Frameworks/libvulkan.1.dylib)
set(DYLIB_MOLTEN_VK ${CMAKE_CURRENT_SOURCE_DIR}/Frameworks/libMoltenVK.dylib)

#file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
#file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE C_HEADERS ${THIRD_PARTY_DIR}/lua/*.h)
file(GLOB_RECURSE C_SOURCES ${THIRD_PARTY_DIR}/lua/*.c)
file(GLOB_RECURSE CPP_MAIN ${MAIN_SOURCE_DIR}/main.cpp)
file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/engine/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/engine/*.cpp)
file(GLOB_RECURSE CPP_PROJECT_HEADERS ${MAIN_SOURCE_DIR}/project/*.hpp)
file(GLOB_RECURSE CPP_PROJECT_SOURCES ${MAIN_SOURCE_DIR}/project/*.cpp)

#ImGUI Files
#file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl.h DESTINATION ../../../third-party/imgui)
#file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl.cpp DESTINATION ../../../third-party/imgui)
#file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.h DESTINATION ../../../third-party/imgui)
#file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp DESTINATION ../../../third-party/imgui)
#file(COPY ${THIRD_PARTY_DIR}/imgui/misc/cpp/imgui_stdlib.h DESTINATION ../../../third-party/imgui)
#file(COPY ${THIRD_PARTY_DIR}/imgui/misc/cpp/imgui_stdlib.cpp DESTINATION ../../../third-party/imgui)

#file(GLOB IMGUI_FILES
#	${THIRD_PARTY_DIR}/imgui/imconfig.h
#	${THIRD_PARTY_DIR}/imgui/imgui.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui.h
#	${THIRD_PARTY_DIR}/imgui/imgui_demo.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui_draw.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui_impl_opengl3.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui_impl_opengl3.h
#	${THIRD_PARTY_DIR}/imgui/imgui_impl_sdl.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui_impl_sdl.h		
#	${THIRD_PARTY_DIR}/imgui/imgui_internal.h
#	${THIRD_PARTY_DIR}/imgui/imgui_tables.cpp
#	${THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp
#	${THIRD_PARTY_DIR}/imgui/imstb_rectpack.h
#	${THIRD_PARTY_DIR}/imgui/imstb_textedit.h
#	${THIRD_PARTY_DIR}/imgui/imstb_truetype.h
#	${THIRD_PARTY_DIR}/imgui/imgui_stdlib.h
#	${THIRD_PARTY_DIR}/imgui/imgui_stdlib.cpp
#)

set(LUA_C_FILES ${C_SOURCES})
list(REMOVE_ITEM LUA_C_FILES ${THIRD_PARTY_DIR}/lua/lua.c)

#Add Compiler definitions to use the Editor
#add_compile_definitions(FORCE_OPENGL)
#add_compile_definitions(RPG_DEBUG)
#add_compile_definitions(RPG_EDITOR)

add_executable(
	rpg-engine-console
	${CPP_MAIN}
	${CPP_HEADERS}
	${CPP_SOURCES}
	${CPP_PROJECT_HEADERS}
	${CPP_PROJECT_SOURCES}
	${C_HEADERS}
	${LUA_C_FILES}
	#${IMGUI_FILES}
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