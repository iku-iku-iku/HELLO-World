cmake_minimum_required(VERSION 3.20.1)

project(HELLO-world)

file(GLOB_RECURSE IMGUI vendor/imgui/*.cpp)
file(GLOB_RECURSE RENDER Rendering/*.cpp)
file(GLOB_RECURSE SHAPE Core/Shape/*.cpp)
file(GLOB_RECURSE Core/Editor Core/Editor/*.cpp)
file(GLOB_RECURSE Core Core/*.cpp)
file(GLOB_RECURSE Lib Lib/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${RENDER} ${IMGUI} vendor/stb_image/stb_image.cpp ${SHAPE} ${Editor} ${Core} ${Lib})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Check all the submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/glfw)

find_package(OpenGL REQUIRED)

# find_package(GLUT REQUIRED)

# find_package(GLEW REQUIRED)
# include_directories(${GLEW_INCLUDE_DIRS})
include_directories("external/glm")
include_directories("vendor/imgui")
include_directories("vendor/stb_image")
include_directories("test")
include_directories(".")
include_directories("Core/Shape")
include_directories("Rendering")
# link_libraries(${GLEW_LIBRARIES})

# target_include_directories(${PROJECT_NAME} 
#     PUBLIC external/glfw/include
# )

# target_link_directories(${PROJECT_NAME} 
#     PUBLIC external/glfw/src
# )

 include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw GLEW ${OPENGL_LIBRARIES} )