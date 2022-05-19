#include <GL/glew.h>
#include <exception>
#include <wavefront/wavefront.h>

#include "renderTexture.h"

RenderTexture::RenderTexture()
{

}

RenderTexture::RenderTexture(int _width, int _height)
{
	//Generate RT frame buffers and check to see if it has been created successfully
	glGenFramebuffers(1, &m_fboId);
	if (!m_fboId)
	{
		throw std::exception();
	}

	//Bind the created frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	//Generate RT textures
	glGenTextures(1, &m_texId);
	//Bind the created textures
	glBindTexture(GL_TEXTURE_2D, m_texId);

	//Set texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Clear the texture bind
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);

	//Generate RT render buffers
	glGenRenderbuffers(1, &m_rboId);
	//Bind render buffers
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	//Store width and height values in the render buffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	//Clear render buffer bind
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);

	//Clear frame buffer bind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{
	//Delete frame and render buffers, as well as textures
	glDeleteFramebuffers(1, &m_fboId);
	glDeleteTextures(1, &m_texId);
	glDeleteRenderbuffers(1, &m_rboId);
}

void RenderTexture::Bind()
{
	//Bind the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::Unbind()
{
	//Unbind the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTexture::GetTexture()
{
	//Return the texture ID
	return m_texId;
}