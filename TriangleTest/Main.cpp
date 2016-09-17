#include "cRenderUtils.h"


void main() {
	
	Window context;
	context.init(1280, 720);

	Framebuffer screen{ 0, 1280, 720 };

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);

	Shader simple = loadShader("../res/shaders/simple.vert",
							  "../res/shaders/simple.frag");


	while (context.step())
	{
		tdraw(simple, quad, screen);
	}

	context.term();
}


//int main() {
//	
//	Window window;
//	window.init(/*800, 600, "Test"*/);
//
//	Vertex  verts[3] = { { 0,  .5f, 0, 1 },
//						 { .5, -.5f, 0, 1 },
//						 { -.5f, -.5f, 0, 1 }};
//
//	unsigned tris[3] = { 0,1,2 };
//
//	const char* vertex_shader =
//		"Version 330\n"
//		"layout(location = 0) in vec4 position;"
//		"void main () { gl_Position = position; }";
//
//	const char* fragmnet_shader =
//		"version 150 \n"
//		"out vec4 outColor"
//		"void main () { outColor = vec4( 1.0, 0.0, 0.0, 1.0); }";
//	
//	Geometry geo = makeGeometry(verts, 3, tris, 3);
//	Shader shader = makeShader(vertex_shader, fragmnet_shader);
//
//	while (window.step()) { draw(shader, geo); };
//
//	freeGeometry(geo);
//	freeShader(shader);
//
//	window.term();
//
//	return 0;
//}