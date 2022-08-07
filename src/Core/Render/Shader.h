#pragma once
#include <string>

namespace SheeEngine
{
	class Shader
	{
	public:
		Shader(const std::string& VertexFilePath, const std::string& FragmentFilePath);
		~Shader();

		void Use() const;
		void UnUse() const;

	private:
		unsigned int ID;   // ID of Program
	};
}

