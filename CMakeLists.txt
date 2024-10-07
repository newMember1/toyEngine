cmake_minimum_required(VERSION 3.10)

set(projectName "toyGame")
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE "Debug")

include_directories(${ROOT_DIR}/include/)
link_directories(${ROOT_DIR}/lib)

file(GLOB RES_FILES *.frag *.vert)
file(GLOB CORE "src/core/*")
file(GLOB VOXELS "src/voxels/*")
file(GLOB UTILS "src/utils/*")
file(GLOB TOYPHYSICS "src/toyPhysics/*")
file(GLOB ENVIRONMENT "src/environment/*")

add_executable(${projectName} ${ROOT_DIR}/src/main.cpp ${ROOT_DIR}/src/scene.cpp ${ROOT_DIR}/src/stb_image.c ${ROOT_DIR}/src/windowProcess.cpp ${ROOT_DIR}/src/glad.c ${RES_FILES} ${CORE} ${VOXELS} ${UTILS} ${TOYPHYSICS} ${ENVIRONMENT})
target_link_libraries(${projectName} ${ROOT_DIR}/lib/libglfw3.a dl m GL X11 pthread)
