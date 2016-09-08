#include "cRenderUtils.h"
#include "window.h"
//Yoloswaggins

int main() {
	
	Window window;
	window.init(800, 600, "Test");



	while (window.step()) {};

	window.term();

	return 0;
}