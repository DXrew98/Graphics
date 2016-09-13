#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include <cstdio>
#include "cRenderUtils.h"

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize)
{
	Geometry retval;

	retval.size = tsize;
	//defining our variables
	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.vao);

	//scope our variables into the buffer (ORDER MATTERS)
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);

	//load in our verts
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	//load in our triangles
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	//Activate a vertex attribute (such as position)
	glEnableVertexAttribArray(0);
	//describe the properties of the attribute (position)
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// unscope our variables (ORDER MATTERS)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry & geo)
{
	glDeleteBuffers(1, &geo.ibo);
	glDeleteBuffers(1, &geo.vbo);
	glDeleteVertexArrays(1, &geo.vao);

	// prevent accidental use
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char * vert, const char * frag)
{
	Shader retval;

	//define
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//assign the source 
	glShaderSource(vs, 1, &vert, NULL);
	glShaderSource(fs, 1, &frag, NULL);

	//compile
	glCompileShader(vs);
	glCompileShader(fs);

	//link
	glAttachShader(retval.handle, fs);
	glAttachShader(retval.handle, vs);
	glLinkProgram(retval.handle);

	//once the program is linked
	//individual shaders aren't needed
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader & shader)
{
	glDeleteProgram(shader.handle);

	//prevent reuse
	shader = { 0 }; 
}

void draw(const Shader & shader, const Geometry & geo)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}
