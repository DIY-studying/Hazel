#include "hzpch.h"
#include "OpenGLTexture.h"
#include "OpenGLError.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Hazel {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channel;
		stbi_set_flip_vertically_on_load(1);
		const unsigned char* data=stbi_load(path.c_str(),&width,&height,&channel,0);
		HZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0,format = 0;
		switch (channel)
		{
		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		default :
			HZ_CORE_ASSERT(false,"Texture format not support!");
			HZ_CORE_ERROR("Texture format not support!");
		}

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID));
		GLCall(glTextureStorage2D(m_RenderID,1, internalFormat, m_Width, m_Height));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data));

		stbi_image_free((void*)data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GLCall(glDeleteTextures(1,&m_RenderID));
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		GLCall(glBindTextureUnit(slot,m_RenderID));
	}

	void OpenGLTexture2D::UnBind() const
	{
		GLCall(glBindTexture(m_RenderID,0));
	}
}
