#pragma once

struct Geometry {

	unsigned vbo, // vertex buffer is the array of vertices (handle)
			 ibo, // index buffer is the array of triangles (handle)
			 vao, // Handle for everything and the memory layout
			 size;
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