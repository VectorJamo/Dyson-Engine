#pragma once

#include <iostream>
#include "../../core.h"

namespace ds {
	namespace maths {
		struct DS vec4
		{
			float x, y, z, w;

			vec4();
			vec4(float x, float y, float z);
			vec4(float x, float y, float z, float w);

			float GetLength();
			vec4 GetNormalVector();
			vec4 Normalize();

			// Vector arithmetic 
			vec4 operator+(const vec4& vec);
			vec4 operator-(const vec4& vec);
			vec4 operator*(const vec4& vec);
			vec4 operator*(const float& scalar);
			vec4 operator/(const vec4& vec);
			vec4 operator/(const float& scalar);

			// Advanced vector arithmetic
			float dot(const vec4& vec);
			vec4 cross(const vec4& vec);

			// Vector comparison 
			bool operator==(const vec4& vec);
			bool operator!=(const vec4& vec);

		};

		DS std::ostream& operator<<(std::ostream& stream, const vec4& vec);
	}
}