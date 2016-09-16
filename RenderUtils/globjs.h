#pragma once
#include "Vertex.h"

struct Geometry {
	unsigned vbo, ibo, vao, size;
};

struct Shader {
	unsigned handle;
};

struct Texture {
	unsigned handle;
	unsigned width, height, format;
};

struct Framebuffer {

	unsigned handle;
	unsigned width, height, nColors;

	Texture depth;
	Texture colors[8];
};