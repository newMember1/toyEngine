cmake_minimum_required(VERSION 3.10)

set(projectName "toyGame")
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories(${ROOT_DIR}/include/)
link_directories(${ROOT_DIR}/lib)

file(GLOB RES_FILES *.frag *.vert)
add_executable(${projectName} ${ROOT_DIR}/src/main.cpp ${ROOT_DIR}/src/voxels/planeVoxel.cpp ${ROOT_DIR}/src/voxels/simpleBallVoxel.cpp ${ROOT_DIR}/src/scene.cpp ${ROOT_DIR}/src/glad.c ${RES_FILES})
target_link_libraries(${projectName} ${ROOT_DIR}/lib/libglfw3.a dl m GL X11 pthread)
