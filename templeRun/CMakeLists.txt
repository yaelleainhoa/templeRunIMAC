cmake_minimum_required(VERSION 2.8)

project(templeRun)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(assimp CONFIG REQUIRED)
message(STATUS ${ASSIMP_INCLUDE_DIRS})

include_directories(${SDL_TTF_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR}  ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

set(ALL_LIBRARIES glimac ${SDL_TTF_LIBRARY} ${ASSIMP_LIBRARIES} ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)
add_subdirectory(jeu)
