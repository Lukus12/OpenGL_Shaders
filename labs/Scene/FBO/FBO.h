#pragma once

#include "../../General_Heading.h"

using namespace std;
using namespace glm;

class FBO
{
public:
	FBO();
	void init(int w, int h, bool multiSamples = false);

	void bind();
	static void unbind();

	void resolveToFbo(FBO& fbo);
	void bindColorTexture(GLenum texUnit = GL_TEXTURE0);
	void bindDepthTexture(GLenum texUnit = GL_TEXTURE1);

private:
	GLuint FBO_Index;
	GLuint colorTex;
	GLuint depthTex;
	int width, height, samples;
};