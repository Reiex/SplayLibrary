# SplayLibrary - [C++] An OpenGL wrapper

SplayLibrary is an OpenGL wrapper built on [SciPP](https://github.com/Reiex/SciPP), [Diskon](https://github.com/Reiex/Diskon), [DejaVu](https://github.com/Reiex/DejaVu), [GLFW](https://www.glfw.org/) and [GLAD](https://github.com/Dav1dde/glad). The goal is to include every feature of [OpenGL 4.6 Core Profile](https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf) in C++ classes - with a lot of compile time verifications and debug tools - and to add some very common tools used with OpenGL: a window handling system, mesh classes, etc.

## Examples

Simple sphere raytracing with varying cube map backgrounds:

https://user-images.githubusercontent.com/13711225/215016729-782e221b-473d-4e1b-b120-2158c65ed02f.mp4

Edge detection of a [Suzanne](https://fr.wikipedia.org/wiki/Blender#Suzanne) mesh using a two passes render with custom framebuffers:

![](https://mpelegrin.hd.free.fr/images/splaylibrary/SuzanneEdges.webp)
