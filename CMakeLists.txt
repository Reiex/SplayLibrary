#######################################################################################################################
##! \file
##! \author Pélégrin Marius
##! \copyright The MIT License (MIT)
##! \date 2022-2023
#######################################################################################################################

# Global project definitions

cmake_minimum_required(VERSION 3.21)

project(SplayLibrary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add external dependencies

if(NOT TARGET scipp)
    set(SCIPP_ADD_EXAMPLES OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SciPP)
endif()

if(NOT TARGET ruc)
    set(RUC_ADD_EXAMPLES OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/Ruc)
endif()

if(NOT TARGET diskon)
    set(DISKON_ADD_EXAMPLES OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/Diskon)
endif()

if(NOT TARGET dejavu)
    set(DEJAVU_ADD_EXAMPLES OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/DejaVu)
endif()

if(NOT TARGET glfw)
    set(BUILD_SHARED_LIBS ON)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/GLFW)
endif()

# SplayLibrary

add_library(
    splaylibrary SHARED
    ${CMAKE_CURRENT_LIST_DIR}/include/glad/glad.h
    ${CMAKE_CURRENT_LIST_DIR}/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/SplayLibrary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/SplayLibraryDecl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/SplayLibraryTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Core.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/CoreDecl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/CoreTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Context.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/DefaultFramebuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Event.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Framebuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/FramebufferAttachable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Renderbuffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Sampler.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/ShaderModule.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/ShaderProgram.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/VertexArray.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Window.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/templates/Buffer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/templates/ShaderProgram.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/templates/Texture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Texture/Texture2D.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Core/Texture/templates/Texture2D.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Private/PrivateIncluded.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Private/PrivateNotIncluded.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Private/templates/PrivateIncluded.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/SplayLibrary/Private/templates/PrivateNotIncluded.hpp
    ${CMAKE_CURRENT_LIST_DIR}/src/glad/glad.c
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/DefaultFramebuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Framebuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/FramebufferAttachable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Renderbuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Sampler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/ShaderModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/ShaderProgram.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/VertexArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Core/Texture/Texture2D.cpp
)

add_dependencies(
    splaylibrary
    scipp
    ruc
    diskon
    dejavu
    glfw
)

target_include_directories(
    splaylibrary
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/SciPP/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/Ruc/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/Diskon/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/DejaVu/include
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/GLFW/include
)

target_compile_definitions(
    splaylibrary
    PUBLIC SPLAYLIBRARY_EXPORTS
)

target_link_libraries(
    splaylibrary
    diskon
    $<TARGET_LINKER_FILE:glfw>
)

# SplayLibrary examples

option(SPLAYLIBRARY_ADD_EXAMPLES "Add target splaylibrary-examples" ON)

if(SPLAYLIBRARY_ADD_EXAMPLES)

    add_executable(
        splaylibrary-examples
        ${CMAKE_CURRENT_LIST_DIR}/examples/main.hpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/advancedLighting/advancedLighting.cpp
        ${CMAKE_CURRENT_LIST_DIR}/examples/basicPhong/basicPhong.cpp
    )

    add_dependencies(
        splaylibrary-examples
        splaylibrary
    )

    target_include_directories(
        splaylibrary-examples
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/SciPP/include
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/Ruc/include
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/Diskon/include
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/external/DejaVu/include
    )

    target_link_libraries(
        splaylibrary-examples
        splaylibrary
    )

endif()
