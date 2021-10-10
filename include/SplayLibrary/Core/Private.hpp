#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef NDEBUG

#define SPL_DEBUG(...) std::printf(__VA_ARGS__)

#else

#define SPL_DEBUG(...)

#endif
