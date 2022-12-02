#include "vec2.h"
namespace ds {
	namespace maths {
		vec2::vec2()
			:x(0.0f), y(0.0f)
		{
		}

		vec2::vec2(float x, float y)
			: x(x), y(y)
		{
		}

		float vec2::GetLength()
		{
			return sqrt(x * x + y * y);
		}

		vec2 vec2::GetNormalVector()
		{
			vec2 normalVec;
			normalVec.x = x / GetLength();
			normalVec.y = y / GetLength();
			return normalVec;
		}

		vec2 vec2::Normalize()
		{
			float length = GetLength();
			x = x / length;
			y = y / length;

			return *this;
		}

		vec2 vec2::GetMidPoint(const vec2& vec) const
		{
			float midX = (x + vec.x) / 2;
			float midY = (y + vec.y) / 2;

			return vec2(midX, midY);
		}

		// Vector arithmetic
		vec2 vec2::operator+(const vec2& vec)
		{
			return vec2((x + vec.x), (y + vec.y));

		}

		vec2 vec2::operator-(const vec2& vec)
		{
			return vec2((x - vec.x), (y - vec.y));

		}
		vec2 vec2::operator*(const vec2& vec)
		{
			return vec2((x * vec.x), (y * vec.y));

		}
		vec2 vec2::operator*(const float& scalar)
		{
			return vec2((x * scalar), (y * scalar));

		}
		vec2 vec2::operator/(const vec2& vec)
		{
			return vec2((x / vec.x), (y / vec.y));

		}
		vec2 vec2::operator/(const float& scalar)
		{
			return vec2((x / scalar), (y / scalar));

		}

		// Advanced vector arithmetic // dot product, corss prodcut
		float vec2::Dot(const vec2& vec)
		{
			return (x * vec.x + y * vec.y);
		}

		// Vector comparison
		bool vec2::operator==(const vec2& vec)
		{
			if (x == vec.x && y == vec.y)
			{
				return true;
			}
			return false;
		}

		bool vec2::operator!=(const vec2& vec)
		{
			if (x == vec.x && y == vec.y)
			{
				return false;
			}
			return true;
		}
		std::ostream& operator<<(std::ostream& stream, const vec2& vec)
		{
			stream << "(" << vec.x << ", " << vec.y << ")";
			return stream;
		}
	}
}