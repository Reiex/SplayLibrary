#include "main.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	int success = 0;

	success &= basicPhongMain();

	return success;
}
