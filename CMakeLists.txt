cmake_minimum_required(VERSION 3.16)
project(HexGame CXX)

# neovim integration for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locate sdl packages automatically
find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)

# define executable name
add_executable(hexLauncher)

# adds the sources files 
target_sources(hexLauncher 
    PRIVATE
        src/main.cpp
        src/SDL_Plotter.cpp
)

# includes the include folder for header files
target_include_directories(hexLauncher PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# link sdl libraries to our executable
target_link_libraries(hexLauncher 
    PRIVATE 
        SDL3::SDL3
        SDL3_mixer::SDL3_mixer
)
