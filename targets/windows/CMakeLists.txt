cmake_minimum_required(VERSION 3.4.1)

project(rpg-engine)

set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third-party")
set(MAIN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../code")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

set(LIB_SDL2 ${THIRD_PARTY_DIR}/sdl-windows/lib/x64/SDL2.lib)
set(LIB_SDL2_MAIN ${THIRD_PARTY_DIR}/sdl-windows/lib/x64/SDL2main.lib)
set(LIB_GLEW ${THIRD_PARTY_DIR}/glew/lib/Release/x64/glew32s.lib)
set(LIB_SDL2_IMAGE ${THIRD_PARTY_DIR}/sdl-image-windows/lib/x64/SDL2_image.lib)
set(LIB_VULKAN ${THIRD_PARTY_DIR}/vulkan-windows/Lib/vulkan-1.lib)

include_directories(${THIRD_PARTY_DIR}/sdl-windows/include)
include_directories(${THIRD_PARTY_DIR}/glew/include)
include_directories(${THIRD_PARTY_DIR}/glm)
include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)
include_directories(${THIRD_PARTY_DIR}/sdl-image-windows/include)
include_directories(${THIRD_PARTY_DIR}/vulkan-windows/Include)
include_directories(${THIRD_PARTY_DIR}/lua)
if(CMAKE_BUILD_TYPE MATCHES "Editor")
	include_directories(${THIRD_PARTY_DIR}/imgui)
	file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
	file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)
else()
	file(GLOB_RECURSE CPP_MAIN ${MAIN_SOURCE_DIR}/main.cpp)
	file(GLOB_RECURSE CPP_HEADERS ${MAIN_SOURCE_DIR}/engine/*.hpp)
	file(GLOB_RECURSE CPP_SOURCES ${MAIN_SOURCE_DIR}/engine/*.cpp)
	file(GLOB_RECURSE CPP_PROJECT_HEADERS ${MAIN_SOURCE_DIR}/project/*.hpp)
	file(GLOB_RECURSE CPP_PROJECT_SOURCES ${MAIN_SOURCE_DIR}/project/*.cpp)
endif()

file(GLOB_RECURSE C_HEADERS ${THIRD_PARTY_DIR}/lua/*.h)
file(GLOB_RECURSE C_SOURCES ${THIRD_PARTY_DIR}/lua/*.c)

# Include required ImGUI files for SDL/OpenGL
if(CMAKE_BUILD_TYPE MATCHES "Editor")
	file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl.h DESTINATION ${THIRD_PARTY_DIR}/imgui)
	file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_sdl.cpp DESTINATION ${THIRD_PARTY_DIR}/imgui)
	file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.h DESTINATION ${THIRD_PARTY_DIR}/imgui)
	file(COPY ${THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp DESTINATION ${THIRD_PARTY_DIR}/imgui)
	file(COPY ${THIRD_PARTY_DIR}/imgui/misc/cpp/imgui_stdlib.h DESTINATION ${THIRD_PARTY_DIR}/imgui)
	file(COPY ${THIRD_PARTY_DIR}/imgui/misc/cpp/imgui_stdlib.cpp DESTINATION ${THIRD_PARTY_DIR}/imgui)

	file(GLOB IMGUI_FILES
		${THIRD_PARTY_DIR}/imgui/imconfig.h
		${THIRD_PARTY_DIR}/imgui/imgui.cpp
		${THIRD_PARTY_DIR}/imgui/imgui.h
		${THIRD_PARTY_DIR}/imgui/imgui_demo.cpp
		${THIRD_PARTY_DIR}/imgui/imgui_draw.cpp
		${THIRD_PARTY_DIR}/imgui/imgui_impl_opengl3.cpp
		${THIRD_PARTY_DIR}/imgui/imgui_impl_opengl3.h
		${THIRD_PARTY_DIR}/imgui/imgui_impl_sdl.cpp
		${THIRD_PARTY_DIR}/imgui/imgui_impl_sdl.h		
		${THIRD_PARTY_DIR}/imgui/imgui_internal.h
		${THIRD_PARTY_DIR}/imgui/imgui_tables.cpp
		${THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp
		${THIRD_PARTY_DIR}/imgui/imstb_rectpack.h
		${THIRD_PARTY_DIR}/imgui/imstb_textedit.h
		${THIRD_PARTY_DIR}/imgui/imstb_truetype.h
		${THIRD_PARTY_DIR}/imgui/imgui_stdlib.h
		${THIRD_PARTY_DIR}/imgui/imgui_stdlib.cpp
	)
endif()

set(LUA_C_FILES ${C_SOURCES})
list(REMOVE_ITEM LUA_C_FILES ${THIRD_PARTY_DIR}/lua/lua.c)

# If we are generating a release build, then request that we produce a Windows desktop
# application executable by specifying WIN32 as an executable option. This avoids the
# console window from appearing when we launch the .exe file. However for debug builds,
# the console window makes it really easy to view logging output so we'll allow it by
# NOT specifying the WIN32 executable option.
if(CMAKE_BUILD_TYPE MATCHES "Release")
	set(EXECUTABLE_TYPE WIN32)
endif()

# Forcing OpenGL Builds
if(CMAKE_BUILD_TYPE MATCHES "OpenGL" OR CMAKE_BUILD_TYPE MATCHES "Editor")
	add_compile_definitions(FORCE_OPENGL)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "OpenGL" OR CMAKE_BUILD_TYPE MATCHES "Editor")
	add_compile_definitions(RPG_DEBUG)	
endif()

if(CMAKE_BUILD_TYPE MATCHES "Editor")
	add_compile_definitions(RPG_EDITOR)
endif()


if(CMAKE_BUILD_TYPE MATCHES "Editor")
	add_executable(
		rpg-engine ${EXECUTABLE_TYPE}
		${CPP_HEADERS}
		${CPP_SOURCES}
		${C_HEADERS}
		${LUA_C_FILES}
		${IMGUI_FILES}
	)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "OpenGL" OR CMAKE_BUILD_TYPE MATCHES "Debug")
	add_executable(
		rpg-engine ${EXECUTABLE_TYPE}
		${CPP_MAIN}
		${CPP_HEADERS}
		${CPP_SOURCES}
		${CPP_PROJECT_HEADERS}
		${CPP_PROJECT_SOURCES}
		${C_HEADERS}
		${LUA_C_FILES}		
	)
endif()

set_property(TARGET rpg-engine PROPERTY CXX_STANDARD 17)
set_property(TARGET rpg-engine PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(
	rpg-engine
	opengl32
	${LIB_GLEW}
	${LIB_SDL2}
	${LIB_SDL2_MAIN}
	${LIB_SDL2_IMAGE}
	${LIB_VULKAN}
)

add_custom_command(
    TARGET rpg-engine
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND PowerShell -File cmake-post-build.ps1
)