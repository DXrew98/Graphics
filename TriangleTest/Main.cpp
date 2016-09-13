#include "cRenderUtils.h"
#include "window.h"
//Yoloswaggins

int main() {
	
	Window window;
	window.init(800, 600, "Test");

	//Vertex  verts[3] = { { 0.0f,  .5f, 0.0f, 1.0f },
	//					{ 0.5f, -.05f, 0.0f, 1.0f },
	//					{ -0.5f, -0.5f, 0.0f, 1.0f } };

	unsigned tris[3] = { 2,1,0 };

	while (window.step()) {};

	window.term();

	return 0;
}