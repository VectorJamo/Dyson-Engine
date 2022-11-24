#include "vec3.h"

namespace ds {
	namespace maths {
		vec3::vec3()
			:x(0.0f), y(0.0f), z(0.0f)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		float vec3::GetLength()
		{
			return sqrt(x * x + y * y + z * z);
		}

		vec3 vec3::GetNormalVector()
		{
			vec3 normalVec;
			normalVec.x = x / GetLength();
			normalVec.y = y / GetLength();
			normalVec.z = z / GetLength();

			return normalVec;
		}

		vec3 vec3::Normalize()
		{
			float length = GetLength();
			x = x / length;
			y = y / length;
			z = z / length;

			return *this;
		}

		// Vector arithmetic
		vec3 vec3::operator+(const vec3& vec)
		{
			return vec3((x + vec.x), (y + vec.y), (z + vec.z));

		}

		vec3 vec3::operator-(const vec3& vec)
		{
			return vec3((x - vec.x), (y - vec.y), (z - vec.z));

		}
		vec3 vec3::operator*(const vec3& vec)
		{
			return vec3((x * vec.x), (y * vec.y), (z * vec.z));

		}
		vec3 vec3::operator*(const float& scalar)
		{
			return vec3((x * scalar), (y * scalar), (z * scalar));

		}
		vec3 vec3::operator/(const vec3& vec)
		{
			return vec3((x / vec.x), (y / vec.y), (z / vec.z));

		}
		vec3 vec3::operator/(const float& scalar)
		{
			return vec3((x / scalar), (y / scalar), (z / scalar));

		}

		// Advanced vector arithmetic // dot product, corss prodcut
		float vec3::dot(const vec3& vec)
		{
			return (x * vec.x + y * vec.y + z * vec.z);
		}
		vec3 vec3::cross(const vec3& vec)
		{
			vec3 crossed;
			crossed.x = (y * vec.z - z * vec.y);
			crossed.y = -(x * vec.z - z * vec.x);
			crossed.z = (x * vec.y - y * vec.x);

			return crossed;
		}

		// Vector comparison
		bool vec3::operator==(const vec3& vec)
		{
			if (x == vec.x && y == vec.y && z == vec.z)
			{
				return true;
			}
			return false;
		}

		bool vec3::operator!=(const vec3& vec)
		{
			if (x == vec.x && y == vec.y && z == vec.z)
			{
				return false;
			}
			return true;
		}
		std::ostream& operator<<(std::ostream& stream, const vec3& vec)
		{
			stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
			return stream;
		}
	}
}