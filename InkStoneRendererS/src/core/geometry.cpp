#include <cmath>

struct vec3;

struct vec2
{
	float x = 0;
	float y = 0;

	vec2() : x(0), y(0) {}

	vec2(float a) : x(a), y(a) {}

	vec2(float x0, float y0) : x(x0), y(y0) {}

	vec2(vec3 v) : x(v.x), y(v.y) {}

	vec2(const vec2& v) : x(v.x), y(v.y) {}

	inline vec2 operator+ (vec2 operand)
	{
		return vec2{ x + operand.x, y + operand.y };
	}

	inline vec2 operator- (vec2 operand)
	{
		return vec2{ x - operand.x, y - operand.y };
	}

	inline vec2 operator* (vec2 operand)
	{
		return vec2{ x * operand.x, y * operand.y };
	}

	inline vec2 operator* (float operand)
	{
		return vec2{ x * operand, y * operand };
	}

	inline vec2 operator/ (vec2 operand)
	{
		return vec2{ x / operand.x, y / operand.y };
	}

	inline vec2 operator/ (float operand)
	{
		return vec2{ x / operand, y / operand };
	}

	inline vec2 operator% (float operand)
	{
		return vec2{ std::fmod(x, operand) , std::fmod(y, operand) };
	}
};

struct vec3
{
	float x = 0;
	float y = 0;
	float z = 0;

	vec3() : x(0), y(0), z(0) {}

	vec3(float a) : x(a), y(a), z(a) {}

	vec3(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}

	vec3(vec2 v, float z0) : x(v.x), y(v.y), z(z0) {}

	vec3(const vec2& v) : x(v.x), y(v.y) {}

	inline vec2 operator+ (vec2 operand)
	{
		return vec2{ x + operand.x, y + operand.y };
	}

	inline vec2 operator- (vec2 operand)
	{
		return vec2{ x - operand.x, y - operand.y };
	}

	inline vec2 operator* (vec2 operand)
	{
		return vec2{ x * operand.x, y * operand.y };
	}

	inline vec2 operator* (float operand)
	{
		return vec2{ x * operand, y * operand };
	}

	inline vec2 operator/ (vec2 operand)
	{
		return vec2{ x / operand.x, y / operand.y };
	}

	inline vec2 operator/ (float operand)
	{
		return vec2{ x / operand, y / operand };
	}

	inline vec2 operator% (float operand)
	{
		return vec2{ std::fmod(x, operand) , std::fmod(y, operand) };
	}
};

float length(vec2 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

vec2 normalize(vec2 v)
{
	return v / length(v);
}