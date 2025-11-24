cmake_minimum_required(VERSION 3.15)
project(GraphicProgrammingAssignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    src/main.cpp
    external/glad/src/glad.c
)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glfw/include
    ${PROJECT_SOURCE_DIR}/external/glad/include
    ${PROJECT_SOURCE_DIR}/external/glm
)

# Link directories
link_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/external/glfw/lib-vc2022
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    opengl32
    glfw3
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    if(MSVC)
        # Set Visual Studio specific flags
        target_compile_options(${PROJECT_NAME} PRIVATE /W3)
        
        # Set subsystem to console
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:CONSOLE"
        )
    endif()
endif()

# Optional: Add DirectX support
option(USE_DIRECTX "Enable DirectX support" OFF)
if(USE_DIRECTX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_DIRECTX)
    target_link_libraries(${PROJECT_NAME}
        d3d11
        dxgi
        d3dcompiler
    )
endif()

# Print build configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "DirectX support: ${USE_DIRECTX}")
