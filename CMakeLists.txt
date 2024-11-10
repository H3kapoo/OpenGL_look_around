cmake_minimum_required(VERSION 3.22)

project(gui)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    #Linux-specific code or configuration here
    message(STATUS "Configuring for Linux")
    set(CXX_STANDARD 23)

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -ggdb -g")
    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../debug)

    # Include paths
    set(FT_LIBRARY_INCLUDE_DIRECTORY "/home/hekapoo/Downloads/freeType2/freetype-2.13.1/include/")
    set(GLEW_LIBRARY_INCLUDE_DIRECTORY "/home/hekapoo/Downloads/glew-2.1.0/include")
    set(GLFW_LIBRARY_INCLUDE_DIRECTORY "/home/hekapoo/Downloads/glfw-3.3.8/include")

    # Path to lib itself
    set(FT_LIBRARY_PATH_DIRECTORY "/home/hekapoo/Downloads/freeType2/freetype-2.13.1/objs/.libs")
    set(GLEW_LIBRARY_PATH_DIRECTORY "/home/hekapoo/Downloads/glew-2.1.0/lib")
    set(GLFW_LIBRARY_PATH_DIRECTORY "/home/hekapoo/Downloads/glfw-3.3.8/src")

    # include_directories (${FT_LIBRARY_INCLUDE_DIRECTORY})
    # include_directories (${GLEW_LIBRARY_INCLUDE_DIRECTORY})
    # include_directories (${GLFW_LIBRARY_INCLUDE_DIRECTORY})

    add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/assetLoaders/TextureLoader.cpp
        src/mesh/Mesh.cpp
        src/mesh/MeshFactory.cpp
        src/renderer/Renderer.cpp
        src/objects/GameObject.cpp
        src/shader/Shader.cpp
        src/tools/Debug.cpp
        src/tools/Logger.cpp
        )

    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

    # Link libs
    # target_link_directories(${PROJECT_NAME} PRIVATE
    #     ${FT_LIBRARY_PATH_DIRECTORY}
    #     ${GLEW_LIBRARY_PATH_DIRECTORY}
    #     ${GLFW_LIBRARY_PATH_DIRECTORY}
    # )

    # Needed for absolute include paths
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

    # sudo apt-get install zlib1g-dev (z)
    # sudo apt-get install libminizip-dev
    target_link_libraries(${PROJECT_NAME} glfw GL GLEW X11)

# If the operating system is not recognized
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()