#pragma once
#include <string>
#include <vector>
#include <memory>

namespace SheeEngine
{
	/**
	* This is a vertex attribute type enumeration that represents the size of the property. 
	* For example, Postion is a vector of vec3, so the size is 3 
	*
	*/
	enum class AttributeType
	{
		Postion   =		3,
		Color     =		3,
		Normal    =		3,
		TexCoords =		2
	};

	/**
	* This is a structure that describes a vertex attribute in the VBO memory layout.
	* And is constructed by passing in 
	* index: the vertex position index.
	* name: the name of the attribute.
	* type: the type of the attribute.
	*/
	struct VertexAttribute
	{
		VertexAttribute(unsigned int index, const std::string& name, AttributeType type, bool isNormalize = false)
			: m_Index(index), m_Name(name), m_Type(type), m_IsNormalize(isNormalize)
		{}


		unsigned int m_Index;

		std::string m_Name;

		AttributeType m_Type;

		bool m_IsNormalize;
	};

	/**
	* This is a class that describes memory layout .
	* And is constructed to accept a VertexAttribute structure wrapped in a vector
	* 
	* 
	*/
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(std::vector<VertexAttribute>& attribute)
			: m_Attribute(attribute)
		{}

		inline std::vector<VertexAttribute>::iterator begin() const { return m_Attribute.begin(); }
		inline std::vector<VertexAttribute>::iterator end() const { return m_Attribute.end(); }

	private:
		std::vector<VertexAttribute>& m_Attribute;
	};


	/**
	* 
	* 
	* 
	*/
	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, unsigned int size, const VertexBufferLayout& layout);
		~VertexBuffer();

		void Bind();
		void UnBind();

		inline VertexBufferLayout& GetVBOLayout() { return m_Layout; }

		inline int GetStride() const { return m_Stride; }

	private:
		unsigned int ID;

		// Used to describe the memory layout of the current buffer object
		VertexBufferLayout m_Layout;

		int m_Stride = 0;

		void CalculateStride();
	};


	/**
	* 
	* 
	* 
	* 
	*/
	class IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* vertices, unsigned int size);
		~IndexBuffer();

		void Bind();
		void UnBind();

	private:
		unsigned int ID;
	};


	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void UnBind();

		void SetVBO(const std::shared_ptr<VertexBuffer>& vbo);
		void SetEBO(const std::shared_ptr<IndexBuffer>& ebo);

	private:
		unsigned int ID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}

