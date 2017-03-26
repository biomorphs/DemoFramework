/*
SDLEngine
Matt Hoyle
*/
#include "shader_binary.h"
#include "utils.h"

namespace Render
{
	ShaderBinary::ShaderBinary()
		: m_handle(0)
	{
	}

	ShaderBinary::~ShaderBinary()
	{
		Destroy();
	}

	inline uint32_t ShaderBinary::TranslateShaderType(ShaderType type) const
	{
		switch (type)
		{
		case ShaderType::VertexShader:
			return GL_VERTEX_SHADER;
		case ShaderType::FragmentShader:
			return GL_FRAGMENT_SHADER;
		default:
			return -1;
		}
	}

	bool ShaderBinary::CompileFromBuffer(ShaderType type, const char* buffer, std::string& resultText)
	{
		return CompileSource(type, buffer, resultText);
	}

	bool ShaderBinary::CompileSource(ShaderType type, const std::string& src, std::string& resultText)
	{
		uint32_t shaderType = TranslateShaderType(type);
		RENDER_ASSERT(shaderType != -1);

		m_handle = glCreateShader(shaderType);
		RENDER_PROCESS_GL_ERRORS_RET("glCreateShader");
		RENDER_ASSERT(m_handle != 0);

		char const* srcPtr = src.c_str();
		glShaderSource(m_handle, 1, &srcPtr, nullptr);
		RENDER_PROCESS_GL_ERRORS_RET("glShaderSource");

		glCompileShader(m_handle);
		RENDER_PROCESS_GL_ERRORS_RET("glCompileShader");

		// check for compile errors
		int32_t compileResult = 0, resultLogSize = 0;
		glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileResult);
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &resultLogSize);

		char errorLogResult[1024] = { '\0' };
		RENDER_ASSERT(resultLogSize < sizeof(errorLogResult));

		glGetShaderInfoLog(m_handle, resultLogSize, nullptr, errorLogResult);
		resultText = errorLogResult;

		m_type = type;

		return compileResult == GL_TRUE;
	}

	void ShaderBinary::Destroy()
	{
		if (m_handle != 0)
		{
			glDeleteShader(m_handle);
			RENDER_PROCESS_GL_ERRORS("glDeleteShader");
		}

		m_handle = 0;
	}
}