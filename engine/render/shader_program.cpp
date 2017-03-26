/*
DemoFramework
Matt Hoyle
*/
#include "shader_program.h"
#include "shader_binary.h"
#include "utils.h"
#include "core/string_hashing.h"

namespace Render
{
	ShaderProgram::ShaderProgram()
		: m_handle(0)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		Destroy();
	}

	bool ShaderProgram::Create(const ShaderBinary& vertexShader, const ShaderBinary& fragmentShader, std::string& result)
	{
		RENDER_ASSERT(vertexShader.GetType() == ShaderType::VertexShader);
		RENDER_ASSERT(fragmentShader.GetType() == ShaderType::FragmentShader);
		RENDER_ASSERT(vertexShader.GetHandle() != 0);
		RENDER_ASSERT(fragmentShader.GetHandle() != 0);

		m_handle = glCreateProgram();
		RENDER_PROCESS_GL_ERRORS_RET("glCreateProgram");

		glAttachShader(m_handle, vertexShader.GetHandle());
		RENDER_PROCESS_GL_ERRORS_RET("glAttachShader");

		glAttachShader(m_handle, fragmentShader.GetHandle());
		RENDER_PROCESS_GL_ERRORS_RET("glAttachShader");

		glLinkProgram(m_handle);
		RENDER_PROCESS_GL_ERRORS_RET("glLinkProgram");

		// check the results
		int32_t linkResult = 0, logLength = 0;
		char resultTxt[1024] = { '\0' };
		glGetProgramiv(m_handle, GL_LINK_STATUS, &linkResult);
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &logLength);

		RENDER_ASSERT(logLength < sizeof(resultTxt));
		glGetProgramInfoLog(m_handle, logLength, NULL, resultTxt);
		result = resultTxt;

		return linkResult == GL_TRUE;
	}

	void ShaderProgram::AddUniform(const char* uniformName)
	{
		RENDER_ASSERT(m_handle != 0);
		const uint32_t uniformHash = Core::StringHashing::GetHash(uniformName);
		RENDER_ASSERT(m_uniformHandles.find(uniformHash) == m_uniformHandles.end());
		uint32_t result = glGetUniformLocation(m_handle, uniformName);
		RENDER_PROCESS_GL_ERRORS("glGetUniformLocation");
		m_uniformHandles[uniformHash] = result;
	}

	uint32_t ShaderProgram::GetUniformHandle(uint32_t nameHash) const
	{
		auto it = m_uniformHandles.find(nameHash);
		RENDER_ASSERT(it != m_uniformHandles.end());
		return it->second;
	}

	uint32_t ShaderProgram::GetUniformHandle(const char* uniformName) const
	{
		const uint32_t uniformHash = Core::StringHashing::GetHash(uniformName);
		return GetUniformHandle(uniformHash);
	}

	void ShaderProgram::Destroy()
	{
		if (m_handle != 0)
		{
			glDeleteProgram(m_handle);
			RENDER_PROCESS_GL_ERRORS("glDeleteProgram");
		}
		
		m_handle = 0;
	}
}
