#pragma once

struct Geometry makeGeometry(const struct Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize);
void freeGeometry(Geometry &);

struct Shader makeShader(const char *vsource, const char *fsource);
void freeShader(Shader &);

// param for channels and bit-depth
struct Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
struct Texture makeTextureF(unsigned square, const float *pixel);
void freeTexture(Texture &t);

struct Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors);
void freeFramebuffer(Framebuffer &fb);