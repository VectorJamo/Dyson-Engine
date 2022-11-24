#include "vec4.h"
namespace ds {
	namespace maths {
		vec4::vec4()
			:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
		{
		}

		vec4::vec4(float x, float y, float z)
			: x(x), y(y), z(z), w(1.0f)
		{
		}

		vec4::vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}

		float vec4::GetLength()
		{
			return sqrt(x * x + y * y + z * z);
		}

		vec4 vec4::GetNormalVector()
		{
			vec4 normalVec;
			normalVec.x = x / GetLength();
			normalVec.y = y / GetLength();
			normalVec.z = z / GetLength();

			return normalVec;
		}

		vec4 vec4::Normalize()
		{
			float length = GetLength();
			x = x / length;
			y = y / length;
			z = z / length;

			return *this;
		}

		// Vector arithmetic
		vec4 vec4::operator+(const vec4& vec)
		{
			return vec4((x + vec.x), (y + vec.y), (z + vec.z));

		}

		vec4 vec4::operator-(const vec4& vec)
		{
			return vec4((x - vec.x), (y - vec.y), (z - vec.z));

		}
		vec4 vec4::operator*(const vec4& vec)
		{
			return vec4((x * vec.x), (y * vec.y), (z * vec.z));

		}
		vec4 vec4::operator*(const float& scalar)
		{
			return vec4((x * scalar), (y * scalar), (z * scalar));

		}
		vec4 vec4::operator/(const vec4& vec)
		{
			return vec4((x / vec.x), (y / vec.y), (z / vec.z));

		}
		vec4 vec4::operator/(const float& scalar)
		{
			return vec4((x / scalar), (y / scalar), (z / scalar));

		}

		// Advanced vector arithmetic // dot product, corss prodcut
		float vec4::dot(const vec4& vec)
		{
			return (x * vec.x + y * vec.y + z * vec.z);
		}
		vec4 vec4::cross(const vec4& vec)
		{
			vec4 crossed;
			crossed.x = (y * vec.z - z * vec.y);
			crossed.y = -(x * vec.z - z * vec.x);
			crossed.z = (x * vec.y - y * vec.x);

			return crossed;
		}

		// Vector comparison
		bool vec4::operator==(const vec4& vec)
		{
			if (x == vec.x && y == vec.y && z == vec.z)
			{
				return true;
			}
			return false;
		}

		bool vec4::operator!=(const vec4& vec)
		{
			if (x == vec.x && y == vec.y && z == vec.z)
			{
				return false;
			}
			return true;
		}
		std::ostream& operator<<(std::ostream& stream, const vec4& vec)
		{
			stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
			return stream;
		}
	}
}