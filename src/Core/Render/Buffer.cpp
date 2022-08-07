#include "seafx.h"
#include "Buffer.h"

#include "glad/glad.h"

namespace SheeEngine
{
	// Vertex Buffer
	VertexBuffer::VertexBuffer(float* vertices, unsigned int size, const VertexBufferLayout& layout)
		: m_Layout(layout)
	{
		glCreateBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		CalculateStride();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::CalculateStride()
	{
		for (auto attrible : m_Layout)
		{
			m_Stride += (int)attrible.m_Type;
		}
	}



	// Index Buffer
	IndexBuffer::IndexBuffer(unsigned int* vertices, unsigned int size)
	{
		glCreateBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}



	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &ID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(ID);
	}
	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVBO(const std::shared_ptr<VertexBuffer>& vbo)
	{
		m_VertexBuffer = vbo;

		ConfigAttribPointor();
	}

	void VertexArray::SetVBO(float* vertices, unsigned int size, const VertexBufferLayout& layout)
	{
		m_VertexBuffer.reset(new VertexBuffer(vertices, size, layout));

		ConfigAttribPointor();
	}

	void VertexArray::SetEBO(const std::shared_ptr<IndexBuffer>& ebo)
	{
		m_IndexBuffer = ebo;
	}

	void VertexArray::SetEBO(unsigned int* vertices, unsigned int size)
	{
		m_IndexBuffer.reset(new IndexBuffer(vertices, size));
	}

	void VertexArray::ConfigAttribPointor()
	{
		int offset = 0;
		for (auto attrible : m_VertexBuffer->GetVBOLayout())
		{
			int size = (int)attrible.m_Type;

			glVertexAttribPointer(attrible.m_Index, size, GL_FLOAT, attrible.m_IsNormalize ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetStride() * sizeof(float), (void*)offset);

			glEnableVertexAttribArray(attrible.m_Index);

			offset += size * sizeof(float);

		}
	}



}
