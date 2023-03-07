#pragma once

#include <cmath>

struct vec2
{
	float x = 0;
	float y = 0;

	inline vec2() : x(0), y(0) {}

	inline vec2(float a) : x(a), y(a) {}

	inline vec2(float x0, float y0) : x(x0), y(y0) {}

	inline vec2(const vec2& v) : x(v.x), y(v.y) {}

	inline vec2 operator+ (const vec2& operand)
	{
		return vec2{ x + operand.x, y + operand.y };
	}

	inline vec2 operator- ()
	{
		return vec2{ -x, -y };
	}

	inline vec2 operator- (const vec2& operand)
	{
		return vec2{ x - operand.x, y - operand.y };
	}

	inline vec2 operator* (const vec2& operand)
	{
		return vec2{ x * operand.x, y * operand.y };
	}

	inline vec2 operator* (float operand)
	{
		return vec2{ x * operand, y * operand };
	}

	inline vec2 operator/ (const vec2& operand)
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

struct vec2i
{
	int x = 0;
	int y = 0;

	inline vec2i() : x(0), y(0) {}

	inline vec2i(int a) : x(a), y(a) {}

	inline vec2i(int x0, int y0) : x(x0), y(y0) {}

	inline vec2i(vec2 v) : x((int)v.x), y((int)v.y) {}

	inline vec2i(const vec2i& v) : x(v.x), y(v.y) {}

	inline vec2i operator+ (const vec2i& operand)
	{
		return vec2i{ x + operand.x, y + operand.y };
	}

	inline vec2i operator- ()
	{
		return vec2i{ -x, -y };
	}

	inline vec2i operator- (const vec2i& operand)
	{
		return vec2i{ x - operand.x, y - operand.y };
	}

	inline vec2i operator* (const vec2i& operand)
	{
		return vec2i{ x * operand.x, y * operand.y };
	}

	inline vec2i operator* (int operand)
	{
		return vec2i{ x * operand, y * operand };
	}

	inline vec2 operator* (float operand)
	{
		return vec2{ x * operand, y * operand };
	}

	inline vec2i operator/ (int operand)
	{
		return vec2i{ x / operand, y / operand };
	}

	inline vec2 operator/ (float operand)
	{
		return vec2{ x / operand, y / operand };
	}

	inline vec2i operator% (int operand)
	{
		return vec2i{ x % operand , y % operand };
	}
};

struct vec3
{
	float x = 0;
	float y = 0;
	float z = 0;

	inline vec3() : x(0), y(0), z(0) {}

	inline vec3(float a) : x(a), y(a), z(a) {}

	inline vec3(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}

	inline vec3(vec2 v, float z0) : x(v.x), y(v.y), z(z0) {}

	inline vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

	inline vec3 operator+ (const vec3& operand)
	{
		return vec3{ x + operand.x, y + operand.y, z + operand.z };
	}

	inline vec3 operator- ()
	{
		return vec3{ -x, -y, -z };
	}

	inline vec3 operator- (const vec3& operand)
	{
		return vec3{ x - operand.x, y - operand.y, z - operand.z };
	}

	inline vec3 operator* (const vec3& operand)
	{
		return vec3{ x * operand.x, y * operand.y, z * operand.z };
	}

	inline vec3 operator* (float operand)
	{
		return vec3{ x * operand, y * operand, z * operand };
	}

	inline vec3 operator/ (const vec3& operand)
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

	inline vec4() : x(0), y(0), z(0), w(0) {}

	inline vec4(float a) : x(a), y(a), z(a), w(a) {}

	inline vec4(float x0, float y0, float z0, float w0) : x(x0), y(y0), z(z0), w(w0) {}

	inline vec4(vec2 v, float z0, float w0) : x(v.x), y(v.y), z(z0), w(w0) {}

	inline vec4(vec3 v, float w0) : x(v.x), y(v.y), z(v.z), w(w0) {}

	inline vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	inline vec4 operator+ (const vec4& operand)
	{
		return vec4{ x + operand.x, y + operand.y, z + operand.z, w + operand.w };
	}

	inline vec4 operator- ()
	{
		return vec4{ -x, -y, -z, -w };
	}

	inline vec4 operator- (const vec4& operand)
	{
		return vec4{ x - operand.x, y - operand.y, z - operand.z, w - operand.w };
	}

	inline vec4 operator* (const vec4& operand)
	{
		return vec4{ x * operand.x, y * operand.y, z * operand.z, w * operand.w };
	}

	inline vec4 operator* (float operand)
	{
		return vec4{ x * operand, y * operand, z * operand, w * operand };
	}

	inline vec4 operator/ (const vec4& operand)
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

	inline vec2 xy()
	{
		return vec2(x, y);
	}

	inline vec3 xyz()
	{
		return vec3(x, y, z);
	}
};

float length(vec2 v);

float length(vec3 v);

float length(vec4 v);

vec2 normalize(vec2 v);

vec3 normalize(vec3 v);

vec4 normalize(vec4 v);

float dot(vec2 v1, vec2 v2);

float dot(vec3 v1, vec3 v2);

float dot(vec4 v1, vec4 v2);

float cross(vec2 v1, vec2 v2);

vec3 cross(vec3 v1, vec3 v2);