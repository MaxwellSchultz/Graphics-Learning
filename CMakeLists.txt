# cmake_minimum_required(VERSION 3.25)

# project(OpenGL)

# set(GLAD_SRC_DIR external/glad/src/)

# set(SOURCES
#     main.cpp
#     ${GLAD_SRC_DIR}gl.c
# )

# add_executable(${PROJECT_NAME} ${SOURCES})

# # add_subdirectory(external/glfw)

# target_include_directories(${PROJECT_NAME} 
#     PUBLIC external/glfw/include
#     PUBLIC external/glad/include
# )

# target_link_directories(${PROJECT_NAME}
#     PUBLIC external/glfw/src
# )   

# target_link_libraries(${PROJECT_NAME}
#     glfw 
# )

cmake_minimum_required(VERSION 3.25)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_DIR /Library/Frameworks/GLFW)

set(GLAD_DIR /Library/Frameworks/GLAD)

set(SOURCES
    main.cpp
    external/glad/src/glad.c
    ${GLFW_DIR}/include/GLFW/glfw3.h
    ${GLFW_DIR}/include/GLFW/glfw3native.h
    ${GLAD_DIR}/include/glad/glad.h
    ${GLAD_DIR}/include/KHR/khrplatform.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(
    PUBLIC ${GLFW_DIR}/include
    PUBLIC ${GLAD_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/lib/libglfw.3.dylib)