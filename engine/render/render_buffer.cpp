/*
DemoFramework
Matt Hoyle
*/
#include "render_buffer.h"
#include "utils.h"
#include <gl/glew.h>

namespace Render
{
	RenderBuffer::RenderBuffer()
		: m_bufferSizeBytes(0)
		, m_handle(0)
	{
	}

	RenderBuffer::~RenderBuffer()
	{
		Destroy();
	}

	inline uint32_t RenderBuffer::TranslateBufferType(RenderBufferType type) const
	{
		switch (type)
		{
		case RenderBufferType::VertexData:
			return GL_ARRAY_BUFFER;
		case RenderBufferType::IndexData:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			return -1;
		}
	}

	uint32_t RenderBuffer::TranslateModificationType(RenderBufferModification type) const
	{
		switch (type)
		{
		case RenderBufferModification::Static:
			return GL_STATIC_DRAW;
		case RenderBufferModification::Dynamic:
			return GL_DYNAMIC_DRAW;
		default:
			return -1;
		}
	}

	bool RenderBuffer::Create(size_t bufferSize, RenderBufferType type, RenderBufferModification modification)
	{
		RENDER_ASSERT(bufferSize > 0, "Buffer size must be >0");

		if (bufferSize > 0)
		{
			auto glBufferType = TranslateBufferType(type);

			glGenBuffers(1, &m_handle);
			RENDER_PROCESS_GL_ERRORS_RET("glGenBuffers");

			glBindBuffer(glBufferType, m_handle);
			RENDER_PROCESS_GL_ERRORS_RET("glBindBuffer");

			// We initialise the buffer memory to the correct size, but we do NOT populate it
			glBufferData(glBufferType, bufferSize, nullptr, GL_STATIC_DRAW);
			RENDER_PROCESS_GL_ERRORS_RET("glBufferData");

			// Reset state
			glBindBuffer(glBufferType, 0);
			RENDER_PROCESS_GL_ERRORS_RET("glBindBuffer");

			m_bufferSizeBytes = bufferSize;
			m_type = type;
		}

		return true;
	}

	void RenderBuffer::SetData(size_t offset, size_t size, void* srcData)
	{
		auto glBufferType = TranslateBufferType(m_type);

		RENDER_ASSERT(offset < m_bufferSizeBytes);
		RENDER_ASSERT((size + offset) <= m_bufferSizeBytes);
		RENDER_ASSERT(srcData != nullptr);
		RENDER_ASSERT(m_handle != 0);

		glBindBuffer(glBufferType, m_handle);
		RENDER_PROCESS_GL_ERRORS("glBindBuffer");

		glBufferSubData(glBufferType, offset, size, srcData);
		RENDER_PROCESS_GL_ERRORS("glBufferSubData");

		glBindBuffer(glBufferType, 0);	// Reset state?
		RENDER_PROCESS_GL_ERRORS("glBindBuffer");
	}

	bool RenderBuffer::Destroy()
	{
		if (m_handle != 0)
		{
			glDeleteBuffers(1, &m_handle);
			RENDER_PROCESS_GL_ERRORS("glDeleteBuffers");
			m_handle = 0;
			m_bufferSizeBytes = 0;
		}

		return true;
	}
}