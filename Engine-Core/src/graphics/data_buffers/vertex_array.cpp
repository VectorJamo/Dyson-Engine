#include "vertex_array.h"

#include <GL/glew.h>

namespace ds {
	namespace graphics {
		VertexArray::VertexArray()
			:pVAO(0), pAttributeIndex(-1)
		{
			glGenVertexArrays(1, &pVAO);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &pVAO);
		}

		void VertexArray::Bind()
		{
			glBindVertexArray(pVAO);
		}

		void VertexArray::Unbind()
		{
			glBindVertexArray(0);
		}
		void VertexArray::PushLayout(int dataType, int dataCount, int stride, int offset)
		{
			pAttributeIndex++;
			
			glEnableVertexAttribArray(pAttributeIndex);
			glVertexAttribPointer(pAttributeIndex, dataCount, dataType, GL_FALSE, stride, (const void*)offset);
		}
	}
}