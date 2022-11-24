#pragma once

#include <iostream>
#include <cmath>

#include "maths/vec/vec2.h"
#include "maths/vec/vec3.h"
#include "maths/vec/vec4.h"

#include <core.h>

namespace ds {
	namespace maths {
		struct DS mat4
		{
			float mat4x4[4][4];
		
			mat4(float diagonal = 1.0f);
			void MakeNull();
			void MakeIdentity();
			
			const float* operator[](int index) const;
		};
		
		// Transformation matrices
		struct DS scale : public mat4
		{
			scale(const vec3& sc);
		
		};
		struct DS translate : public mat4
		
		{
			translate(const vec3& tr);
		};
		struct DS rotate : public mat4
		{
			rotate(float angle, const vec3& rot);
			rotate(float angle, const vec2& rot);
		
		};
		
		// Pojection matrices
		struct DS orthographic :public mat4
		{
			orthographic(float left, float right, float top, float bottom, float znear, float zfar);
		};
		
		// Matrix - Vector multiplication
		DS vec4 operator*(const mat4& mat, const vec4& vec);
		
		// Matrix - Matrix multiplication
		DS mat4 operator* (const mat4& mat1, const mat4& mat2);
		
		// For printing matrix object to the console
		DS std::ostream& operator<<(std::ostream& stream, const mat4& mat);
	} 
}
