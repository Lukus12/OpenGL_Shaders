#include "FBO.h"

FBO::FBO()
{
	width = 0;
	height = 0;
	samples = 8;
	colorTex = 0;
	depthTex = 0;
}

void FBO::init(int w, int h, bool multiSamples)
{
	this->width = w;
	this->height = h;

	glGenFramebuffers(1, &FBO_Index);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO_Index);

	if (colorTex != 0) {
		glDeleteTextures(1, &colorTex);
	}
	if (depthTex != 0) {
		glDeleteTextures(1, &depthTex);
	}

	if (multiSamples) {
		glGenTextures(1, &colorTex);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorTex);

		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, w, h, false);

		glGenTextures(1, &depthTex);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthTex);

		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH_COMPONENT24, w, h, false);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, depthTex, 0);
	}
	else {
		glGenTextures(1, &colorTex);
		glBindTexture(GL_TEXTURE_2D, colorTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &depthTex);
		glBindTexture(GL_TEXTURE_2D, depthTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
	}

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		cout << "FBO creation failed\n";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO_Index);
}

void FBO::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::resolveToFbo(FBO& fbo)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->FBO_Index);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.FBO_Index);
	glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, fbo.width, fbo.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, fbo.width, fbo.height, GL_DEPTH_BUFFER_BIT, GL_LINEAR);
}

void FBO::bindColorTexture(GLenum texUnit)
{
	glActiveTexture(texUnit);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, colorTex);
}

void FBO::bindDepthTexture(GLenum texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, depthTex);
}