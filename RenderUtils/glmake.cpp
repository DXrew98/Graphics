#include "gldecs.h"
#include "glmake.h"
#include "globjs.h"
#include "Vertex.h"

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize){

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
	glEnableVertexAttribArray(0);	// position
	glEnableVertexAttribArray(1);	// color
	glEnableVertexAttribArray(2);	// normal
	glEnableVertexAttribArray(3);	// tex coordinates


	// index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	// unscope our variables (ORDER MATTERS)
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	retval.size = tsize;
	return retval;
}

void freeGeometry(Geometry & geo){

	glDeleteBuffers(1, &geo.ibo);
	glDeleteBuffers(1, &geo.vbo);
	glDeleteVertexArrays(1, &geo.vao);

	// prevent accidental use
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char * vsource, const char * fscource){

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

void freeShader(Shader & shader){

	glDeleteProgram(shader.handle);

	//prevent reuse
	shader.handle = { 0 };
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char * pixels){

	Texture retval = { 0, width, height, format };

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}



Texture makeTextureF(unsigned square, const float * pixels){

	Texture retval = { 0, square, square, GL_RED }; // GL_RED, GL_RG, GL_RGB, GL_RGBA

	glGenTextures( 1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	return retval;
}

void freeTexture(Texture &t) {

	glDeleteTextures(1, &t.handle);
	t = { 0, 0, 0, 0 };
}

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors)
{
	Framebuffer retval = { 0, width, height, nColors };

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	//////////////////////////////////////////////////////////////////////////////
	retval.depth = makeTexture(width, height, GL_DEPTH_COMPONENT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);	
	/////////////////////////////////////////////////////////////////////////////

	const GLenum attachments[8] = {
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7
	};

	for (int i = 0; i < nColors && i < 8; ++i) {

		retval.colors[i] = makeTexture(width, height, GL_RGBA, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.colors[i].handle, 0);
	}

	glDrawBuffers(nColors, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return retval;
}

void freeFramebuffer(Framebuffer &fb) {
	for (unsigned i = 0; i < fb.nColors; ++i) {
		freeTexture(fb.colors[i]);
	}

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0, 0, 0, 0, };
}
