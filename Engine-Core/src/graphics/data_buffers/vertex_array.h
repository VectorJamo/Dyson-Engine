#pragma once
#include "core.h"

namespace ds {
	namespace graphics {
		class DS VertexArray
		{
		private:
			unsigned int pVAO;
			int pAttributeIndex;

		public:
			VertexArray();
			~VertexArray();

			void Bind();
			void Unbind();

			void PushLayout(int dataType, int dataCount, int stride, int offset);

		};

	}
}
