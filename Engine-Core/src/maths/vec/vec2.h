#pragma once

#include <iostream>
#include <cmath>
#include <core.h>

namespace ds {
	namespace maths {

		struct DS vec2
		{
			float x, y;

			vec2();
			vec2(float x, float y);

			float GetLength();
			vec2 GetNormalVector();
			vec2 Normalize();

			// Vector arithmetic 
			vec2 operator+(const vec2& vec);
			vec2 operator-(const vec2& vec);
			vec2 operator*(const vec2& vec);
			vec2 operator*(const float& scalar);
			vec2 operator/(const vec2& vec);
			vec2 operator/(const float& scalar);

			// Advanced vector arithmetic
			float Dot(const vec2& vec);

			// Vector comparison 
			bool operator==(const vec2& vec);
			bool operator!=(const vec2& vec);

		};

		DS std::ostream& operator<<(std::ostream& stream, const vec2& vec);
	}
}