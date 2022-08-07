#include "seafx.h"
#include "Shader.h"

#include <glad/glad.h>



namespace SheeEngine
{
	Shader::Shader(const std::string& VertexFilePath, const std::string& FragmentFilePath)
	{
		/* shader code which have some logical statement, language is GLSL */
		std::string vertexCode;
		std::string fragmentCode;
	
		/* files which storage GLSL statement */
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
	
		/* read data from file should check exceptions */
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			/* open the shader file */
			vShaderFile.open(VertexFilePath);
			fShaderFile.open(FragmentFilePath);
	
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;
	
			/* read buffer in file thought stream */
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
	
			vShaderFile.close();
			fShaderFile.close();
	
			/* stringstream to string */
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}

		/* string to char* */
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShader, 1, &vShaderCode, 0);
		glCompileShader(VertexShader);

		int success = 0;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);

			glDeleteShader(VertexShader);

			SENGINE_LOG_ERROR("error::shader::vertex::compile_fail\n");
			SENGINE_LOG_ERROR("{0}", infoLog);

			return;
		}

		unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShader, 1, &fShaderCode, 0);
		glCompileShader(FragmentShader);

		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);

			glDeleteShader(FragmentShader);

			SENGINE_LOG_ERROR("error::shader::Fragment::compile_fail\n");
			SENGINE_LOG_ERROR("{0}", infoLog);

			return;
		}

		ID = glCreateProgram();
		unsigned int Program = ID;

		glAttachShader(Program, VertexShader);
		glAttachShader(Program, FragmentShader);

		glLinkProgram(Program);

		glGetProgramiv(Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(Program, 512, NULL, infoLog);

			glDeleteProgram(Program);
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			SENGINE_LOG_ERROR("error::shader::Program::link_fail\n");
			SENGINE_LOG_ERROR("{0}", infoLog);

			return;
		}

		glDetachShader(Program, VertexShader);
		glDetachShader(Program, VertexShader);
		
	}

	Shader::~Shader()
	{
		glDeleteProgram(ID);
	}

	void Shader::Use() const
	{
		glUseProgram(ID);
	}

	void Shader::UnUse() const
	{
		glUseProgram(0);
	}
}
