#include "cRenderUtils.h"
#include "glm\ext.hpp"


void main() {
	
	Window context;
	context.init(1280, 720);
	
	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	Shader simple = loadShader("../res/shaders/simple.vert",
							   "../res/shaders/simple.frag");

	Shader post = loadShader("../res/shaders/post.vert",
							  "../res/shaders/post.frag");

	Framebuffer screen{ 0, 1280, 720 };
	Framebuffer frame = makeFramebuffer(1280, 720, 2);

	glm::mat4 model, view, proj;

	model = glm::translate(glm::vec3(0, -1, 0));
	view  = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	proj  = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;

	while (context.step()){

		time += 0.016f;
		clearFramebuffer(frame);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		tdraw(simple, spear, frame, model, view, proj, spear_diffuse, spear_normal, spear_specular);

		tdraw(post, quad, screen, frame.colors[0], frame.colors[1]);
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