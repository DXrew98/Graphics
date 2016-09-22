#include "gldecs.h"
#include "glmake.h"
#include "globjs.h"
#include "Vertex.h"

//#define STB_IMAGE_IMPLIMENTATION
//#include "stb\stb_image.h"
//
//#define TINYOBJLOADER_IMPLIMENTATION
//#include "tiny_obj_loader.h5

#include <fstream>
#include <istream>
#include <string>

std::string cppStyleFileToString(const char *path) {

	glog("Loading Shader", path);
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
	return file_contents;
}

Shader loadShader(const char * vpath, const char * fpath){

	std::string vs = cppStyleFileToString(vpath);
	std::string fs = cppStyleFileToString(fpath);

	glog("Vertex Shader: ", vs);
	glog("Fragment Shader: ", fs);

	return makeShader(vs.c_str(), fs.c_str());
}

Texture loadTexture(const char * path)
{
	glog("Loading Texture", path);

	int w, h, f;
	unsigned char *p;

	Texture retval = { 0, 0, 0, 0 };

	//stbi_set_flip_vertically_on_load(true);
	//p = stbi_load(path, &w, &h, &f, STBI_default);

	//if (!p) return retval;

	//switch (f) {

	//case STBI_grey: f = GL_RED; break;
	//case STBI_grey_alpha: f = GL_RG; break;
	//case STBI_rgb: f = GL_RGB; break;
	//case STBI_rgb_alpha: f = GL_RGBA; break;
	//}

	//retval = makeTexture(w, h, f, p);
	//stbi_image_free(p);

	return retval;
}

Geometry loadOBJ(const char * path){

	glog("TODO", "Eliminate redundent vertices.");
	
	//tinyobj::attrib_t attrib;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;

	//std::string err;
	//bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
	//int vsize = shapes[0].mesh.indices.size();

	//Vertex   *verts = new Vertex[vsize];
	//unsigned * tris = new unsigned[vsize];

	//for (int i = 0; i < vsize; ++i) {

	//	auto ind = shapes[0].mesh.indices[i];

	//	const float *n = &attrib.normals[ind.normal_index * 3];
	//	const float *p = &attrib.vertices[ind.vertex_index * 3];

	//	verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
	//	verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.f);

	//	if (ind.texcoord_index >= 0) {

	//		const float *t = &attrib.texcoords[ind.texcoord_index * 2];
	//		verts[i].texcoord = glm::vec2(t[0], t[1]);
	//	}
	//	tris[i] = i;
	//}

	//retval = makeGeometry(verts, vsize, tris, vsize);

	/*Geometry retval = makeGeometry{ verts, vsize, tris, t[1] };*/
	Geometry retval = { 0,0,0,0 };

	//delete[] verts;
	//delete[] tris;

	return retval;
}
