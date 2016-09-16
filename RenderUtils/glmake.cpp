#include "gldecs.h"
#include "glmake.h"

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize)
{
	Geometry retval;


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

	// Attributes let us tell openGL how the memory is laid out
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);

	// unscope our variables (ORDER MATTERS)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	retval.size = tsize;
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

Shader makeShader(const char * vsource, const char * fscource)
{
	glog("TODO", "Find a way to implement state management");

	Shader retval;

	//define
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//assign the source 
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fscource, NULL);

	//compile
	glCompileShader(vs);
	glCompileShader(fs);

	//link
	glAttachShader(retval.handle, fs);
	glAttachShader(retval.handle, vs);
	glLinkProgram(retval.handle);
	/*glog_glLinkProgram(retval.handle);*/ // error handeling version

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
	shader.handle = { 0 };
}