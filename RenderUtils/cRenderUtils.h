
struct vertex {
	float position[4] = { 0, 0, 0, 1 };
};

struct Geometry {
	
	unsigned vao, vbo, ibo, size;
};

Geometry makeGeometry(const Vertex * verts. )