#pragma once

struct Geometry makeGeometry(const struct Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize);
void freeGeometry(Geometry &);

struct Shader makeShader(const char *vsource, const char *fsource, bool depth = true, bool add = false, bool face = true);
void freeShader(Shader &);

// param for channels and bit-depth
struct Texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);
struct Texture makeTextureF(unsigned square, const float *pixel);
void freeTexture(Texture &t);

struct Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors);
void freeFramebuffer(Framebuffer &fb);