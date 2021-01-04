#!/bin/bash

# Include the shared scripts from the parent folder
. ../../shared/shared-scripts.sh

# Ask Homebrew to fetch our required programs
fetch_brew_dependency "wget"
fetch_brew_dependency "cmake"
fetch_brew_dependency "ninja"

# Fetch 3rd party files
fetch_third_party_lib_sdl
fetch_third_party_lib_sdl_image
fetch_third_party_lib_glm
fetch_third_party_lib_tiny_obj_loader
fetch_third_party_lib_vulkan_macos
fetch_third_party_lib_lua
fetch_third_party_lib_imgui

# Fetch Framework files
fetch_framework_sdl2
fetch_framework_sdl2_image

# Setup libs
setup_vulkan_libs_macos

compile_vulkan_shaders