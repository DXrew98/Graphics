#pragma once
#include "globjs.h"

Geometry makeGeometry(const struct Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize);
void freeGeometry(Geometry &geo);

Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &shader);

//Texture makeTexture(unsigned 
//{
//
//};)