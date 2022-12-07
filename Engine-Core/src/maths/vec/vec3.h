#pragma once

#include <iostream>
#include "../../core.h"

namespace ds {
	namespace maths {
		struct DS vec3
		{
			float x, y, z;

			vec3();
			vec3(float x, float y, float z);

			float GetLength();
			vec3 GetNormalVector();
			vec3 Normalize();

			// Vector arithmetic 
			vec3 operator+(const vec3& vec);
			vec3 operator-(const vec3& vec);
			vec3 operator*(const vec3& vec);
			vec3 operator*(const float& scalar);
			vec3 operator/(const vec3& vec);
			vec3 operator/(const float& scalar);

			// Advanced vector arithmetic
			float dot(const vec3& vec);
			vec3 cross(const vec3& vec);

			// Vector comparison 
			bool operator==(const vec3& vec);
			bool operator!=(const vec3& vec);

		};

		DS std::ostream& operator<<(std::ostream& stream, const vec3& vec);
	}
}