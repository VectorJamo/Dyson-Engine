#include "mat4.h"
namespace ds {
	namespace maths {
		mat4::mat4(float diagonal)
		{
			MakeNull();
			for (int i = 0; i < 4; i++)
			{
				mat4x4[i][i] = diagonal;
			}
		}
		void mat4::MakeNull()
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					mat4x4[i][j] = 0.0f;
				}
			}
		}
		void mat4::MakeIdentity()
		{
			MakeNull();
			for (int i = 0; i < 4; i++)
			{
				mat4x4[i][i] = 1.0f;
			}
		}

		const float* mat4::operator[](int index) const
		{
			return mat4x4[index];
		}

		// Transformation matrices
		// Scale
		scale::scale(const vec3& sc)
		{
			mat4x4[0][0] = sc.x;
			mat4x4[1][1] = sc.y;
			mat4x4[2][2] = sc.z;
		}
		// Translate
		translate::translate(const vec3& tr)
		{
			mat4x4[0][3] = tr.x;
			mat4x4[1][3] = tr.y;
			mat4x4[2][3] = tr.z;
		}
		//Rotate
		rotate::rotate(float angle, const vec3& rot)
		{
			if (rot.x)
			{
				mat4x4[1][1] = cos(angle);
				mat4x4[1][2] = -sin(angle);
				mat4x4[2][1] = sin(angle);
				mat4x4[2][2] = cos(angle);
			}
			else if (rot.y)
			{
				mat4x4[0][0] = cos(angle);
				mat4x4[0][2] = sin(angle);
				mat4x4[2][0] = -sin(angle);
				mat4x4[2][2] = cos(angle);
			}
			else if (rot.z)
			{
				mat4x4[0][0] = cos(angle);
				mat4x4[0][1] = -sin(angle);
				mat4x4[1][0] = sin(angle);
				mat4x4[1][1] = cos(angle);
			}
		}

		rotate::rotate(float angle, const vec2& rot)
		{
			mat4x4[0][0] = cos(angle);
			mat4x4[0][1] = -sin(angle);
			mat4x4[0][2] = -rot.x * cos(angle) + rot.y * sin(angle) + rot.x;

			mat4x4[1][0] = sin(angle);
			mat4x4[1][1] = cos(angle);
			mat4x4[1][2] = -rot.x * sin(angle) - rot.y * cos(angle) + rot.y;
		}

		// Projection matrices
		// Orthographic projection matrix
		orthographic::orthographic(float left, float right, float top, float bottom, float znear, float zfar)
		{

			mat4x4[0][0] = 2 / (right - left);
			mat4x4[1][1] = 2 / (top - bottom);
			mat4x4[2][2] = -2 / (zfar - znear);

			mat4x4[0][3] = -((right + left) / (right - left));
			mat4x4[1][3] = -((top + bottom) / (top - bottom));
			mat4x4[2][3] = -((zfar + znear) / (zfar - znear));
		}

		// Matrix - Vector multiplication
		vec4 operator*(const mat4& mat, const vec4& vec)
		{
			vec4 newVec;
			newVec.x = mat.mat4x4[0][0] * vec.x + mat.mat4x4[0][1] * vec.y + mat.mat4x4[0][2] * vec.z + mat.mat4x4[0][3] * vec.w;
			newVec.y = mat.mat4x4[1][0] * vec.x + mat.mat4x4[1][1] * vec.y + mat.mat4x4[1][2] * vec.z + mat.mat4x4[1][3] * vec.w;
			newVec.z = mat.mat4x4[2][0] * vec.x + mat.mat4x4[2][1] * vec.y + mat.mat4x4[2][2] * vec.z + mat.mat4x4[2][3] * vec.w;
			newVec.w = mat.mat4x4[3][0] * vec.x + mat.mat4x4[3][1] * vec.y + mat.mat4x4[3][2] * vec.z + mat.mat4x4[3][3] * vec.w;

			return newVec;
		}

		// Matrix - Matrix multiplication
		// This took quit a while to figure out :P
		mat4 operator* (const mat4& mat1, const mat4& mat2)
		{
			mat4 newMat;
			for (int i = 0; i < 4; i++)
			{
				newMat.mat4x4[i][0] = mat1.mat4x4[i][0] * mat2.mat4x4[0][0] + mat1.mat4x4[i][1] * mat2.mat4x4[1][0] + mat1.mat4x4[i][2] * mat2.mat4x4[2][0] + mat1.mat4x4[i][3] * mat2.mat4x4[3][0];
				newMat.mat4x4[i][1] = mat1.mat4x4[i][0] * mat2.mat4x4[0][1] + mat1.mat4x4[i][1] * mat2.mat4x4[1][1] + mat1.mat4x4[i][2] * mat2.mat4x4[2][1] + mat1.mat4x4[i][3] * mat2.mat4x4[3][1];
				newMat.mat4x4[i][2] = mat1.mat4x4[i][0] * mat2.mat4x4[0][2] + mat1.mat4x4[i][1] * mat2.mat4x4[1][2] + mat1.mat4x4[i][2] * mat2.mat4x4[2][2] + mat1.mat4x4[i][3] * mat2.mat4x4[3][2];
				newMat.mat4x4[i][3] = mat1.mat4x4[i][0] * mat2.mat4x4[0][3] + mat1.mat4x4[i][1] * mat2.mat4x4[1][3] + mat1.mat4x4[i][2] * mat2.mat4x4[2][3] + mat1.mat4x4[i][3] * mat2.mat4x4[3][3];

			}
			return newMat;
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& mat)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					stream << mat.mat4x4[i][j] << ", ";
				}
				stream << std::endl;
			}
			return stream;
		}
	}
}