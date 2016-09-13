
struct Vertex {
	float position[4] = { 0, 0, 0, 1 };
};

struct Geometry {
	
	unsigned vao, vbo, ibo, size;
};

Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize);

void freeGeometry(Geometry &geo);

struct Shader { unsigned handle; };

Shader makeShader(const char *vert, const char *frag);
void freeShader(Shader &shader);

void draw(const Shader &shader, const Geometry &geo);