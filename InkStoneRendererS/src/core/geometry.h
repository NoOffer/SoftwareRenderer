#pragma once

#include <cmath>

struct vec2
{
	float x = 0;
	float y = 0;

	vec2() : x(0), y(0) {}

	vec2(float a) : x(a), y(a) {}

	vec2(float x0, float y0) : x(x0), y(y0) {}

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

	vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

	inline vec3 operator+ (vec3 operand)
	{
		return vec3{ x + operand.x, y + operand.y, z + operand.z };
	}

	inline vec3 operator- (vec3 operand)
	{
		return vec3{ x - operand.x, y - operand.y, z - operand.z };
	}

	inline vec3 operator* (vec3 operand)
	{
		return vec3{ x * operand.x, y * operand.y, z * operand.z };
	}

	inline vec3 operator* (float operand)
	{
		return vec3{ x * operand, y * operand, z * operand };
	}

	inline vec3 operator/ (vec3 operand)
	{
		return vec3{ x / operand.x, y / operand.y, z / operand.z };
	}

	inline vec3 operator/ (float operand)
	{
		return vec3{ x / operand, y / operand, z / operand };
	}

	inline vec3 operator% (float operand)
	{
		return vec3{ std::fmod(x, operand), std::fmod(y, operand), std::fmod(z, operand) };
	}
};

struct vec4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	vec4() : x(0), y(0), z(0), w(0) {}

	vec4(float a) : x(a), y(a), z(a), w(a) {}

	vec4(float x0, float y0, float z0, float w0) : x(x0), y(y0), z(z0), w(w0) {}

	vec4(vec2 v, float z0, float w0) : x(v.x), y(v.y), z(z0), w(w0) {}

	vec4(vec3 v, float w0) : x(v.x), y(v.y), z(v.z), w(w0) {}

	vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	inline vec4 operator+ (vec4 operand)
	{
		return vec4{ x + operand.x, y + operand.y, z + operand.z, w + operand.w };
	}

	inline vec4 operator- (vec4 operand)
	{
		return vec4{ x - operand.x, y - operand.y, z - operand.z, w - operand.w };
	}

	inline vec4 operator* (vec4 operand)
	{
		return vec4{ x * operand.x, y * operand.y, z * operand.z, w * operand.w };
	}

	inline vec4 operator* (float operand)
	{
		return vec4{ x * operand, y * operand, z * operand, w * operand };
	}

	inline vec4 operator/ (vec4 operand)
	{
		return vec4{ x / operand.x, y / operand.y, z / operand.z, w / operand.w };
	}

	inline vec4 operator/ (float operand)
	{
		return vec4{ x / operand, y / operand, z / operand, w / operand };
	}

	inline vec4 operator% (float operand)
	{
		return vec4{ std::fmod(x, operand), std::fmod(y, operand), std::fmod(z, operand), std::fmod(w, operand) };
	}
};

float length(vec2 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float length(vec3 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float length(vec4 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec2 normalize(vec2 v)
{
	return v / length(v);
}

vec3 normalize(vec3 v)
{
	return v / length(v);
}

vec4 normalize(vec4 v)
{
	return v / length(v);
}

float dot(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float dot(vec3 v1, vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float dot(vec4 v1, vec4 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float cross(vec2 v1, vec2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

vec3 cross(vec3 v1, vec3 v2)
{
	return vec3{ v1.y * v2.z - v1.z * v2.y, v1.x * v2.z - v1.z * v2.x, v1.x * v2.y - v1.y * v2.x };
}