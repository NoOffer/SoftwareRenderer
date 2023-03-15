#include "Renderer.h"

#include <iostream>

Renderer::Renderer(int width, int height, Camera* cam) : m_Width(width), m_Height(height), m_Camera(cam), m_DeltaTime(0)
{
	m_FrameBuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 3);
	if (m_FrameBuffer) memset(m_FrameBuffer, 0, sizeof(unsigned char) * width * height * 3);

	m_ZBuffer = (float*)malloc(sizeof(float) * width * height);
	if (m_ZBuffer) for (int i = 0; i < width * height; i++) m_ZBuffer[i] = 2.0f;

	m_CurrentTimeMS = clock();
}

Renderer::~Renderer()
{
	free(m_FrameBuffer);
	free(m_ZBuffer);
}

void Renderer::ClearBuffer()
{
	memset(m_FrameBuffer, 0, sizeof(unsigned char) * m_Width * m_Height * 3);
	for (int i = 0; i < m_Width * m_Height; i++) m_ZBuffer[i] = 2.0f;
}

//void Renderer::Draw(Model& model)
//{
//	mat4 viewMatrix = (*m_Camera).GetViewMatrix();
//	mat4 projMatrix = (*m_Camera).GetProjMatrix();
//
//	VertexBuffer& vb = model.GetVertexBuffer();
//	IndexBuffer& ib = model.GetIndexBuffer();
//
//	for (int i = 0; i < ib.GetCount(); i += 3)
//	{
//		//DrawTriangle(
//		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i]], 1.0f))).xyz(),
//		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i + 1]], 1.0f))).xyz(),
//		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i + 2]], 1.0f))).xyz(),
//		//	{ 240, 240, 255 });
//
//		vec4 a = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i]], 1.0f)));
//		vec4 b = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i + 1]], 1.0f)));
//		vec4 c = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i + 2]], 1.0f)));
//		a.x /= std::abs(a.w);
//		a.y /= std::abs(a.w);
//		b.x /= std::abs(b.w);
//		b.y /= std::abs(b.w);
//		c.x /= std::abs(c.w);
//		c.y /= std::abs(c.w);
//		DrawTriangle(a.xyz(), b.xyz(), c.xyz(), { 240, 240, 255 });
//	}
//
//	DrawLine(vec2i(0, 0), vec2i(m_Width - 1, 0), { 255, 0, 0 });
//	DrawLine(vec2i(m_Width - 1, 0), vec2i(m_Width - 1, m_Height - 1), { 255, 0, 0 });
//
//	// Time
//	m_DeltaTime = (clock() - (float)m_CurrentTimeMS) / CLOCKS_PER_SEC;
//	m_CurrentTimeMS = clock();
//
//	//std::cout << 1 / m_DeltaTime << std::endl;
//}

void Renderer::Draw(Model& model)
{
	mat4 projMatrix = (*m_Camera).GetProjMatrix();
	mat4 viewMatrix = (*m_Camera).GetViewMatrix();

	VertexBuffer& vb = model.GetVertexBuffer();
	IndexBuffer& ib = model.GetIndexBuffer();

	for (int i = 0; i < ib.GetCount(); i += 3)
	{
		//DrawTriangle(
		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i]], 1.0f))).xyz(),
		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i + 1]], 1.0f))).xyz(),
		//	(*m_Camera).Project(mul(viewMatrix, vec4(vb[ib[i + 2]], 1.0f))).xyz(),
		//	{ 240, 240, 255 });

		vec4 a = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i]], 1.0f)));
		vec4 b = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i + 1]], 1.0f)));
		vec4 c = mul(projMatrix, mul(viewMatrix, vec4(vb[ib[i + 2]], 1.0f)));
		DrawTriangle((a / std::abs(a.w)).xyz(), (b / std::abs(b.w)).xyz(), (c / std::abs(c.w)).xyz(), { 240, 240, 255 });
	}

	DrawLine(vec2i(0, 0), vec2i(m_Width - 1, 0), { 255, 0, 0 });
	DrawLine(vec2i(m_Width - 1, 0), vec2i(m_Width - 1, m_Height - 1), { 255, 0, 0 });

	// Time
	m_DeltaTime = (clock() - (float)m_CurrentTimeMS) / CLOCKS_PER_SEC;
	m_CurrentTimeMS = clock();

	//std::cout << 1 / m_DeltaTime << std::endl;
}

unsigned char const* Renderer::GetFrameBuffer()
{
	return (unsigned char const*)m_FrameBuffer;
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1, const ColorRGB& color)
{
	// Temporary confinement
	x0 = min(max(x0, 0), m_Width);
	y0 = min(max(y0, 0), m_Height);
	x1 = min(max(x1, 0), m_Width);
	y1 = min(max(y1, 0), m_Height);

	int dx = std::abs(x0 - x1);
	int dy = std::abs(y0 - y1);
	bool steep = false;
	if (dy > dx)
	{
		// Ensure X as main
		std::swap(x0, y0);
		std::swap(x1, y1);
		std::swap(dx, dy);
		steep = true;
	}

	int error = 0;
	if (x0 > x1)
	{
		// Ensure left−to−right 
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int j = y0;
	for (int i = x0; i <= x1; i++)
	{
		int idx;
		if (steep)
		{
			idx = (i * m_Width + j) * 3;
		}
		else
		{
			idx = (j * m_Width + i) * 3;
		}
		m_FrameBuffer[idx] = color.r;
		m_FrameBuffer[idx + 1] = color.g;
		m_FrameBuffer[idx + 2] = color.b;

		error += dy * 2;
		if (error > dx)
		{
			j += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void Renderer::DrawLine(vec2i x, vec2i y, const ColorRGB& color)
{
	DrawLine(x.x, x.y, y.x, y.y, color);
}

vec3 Renderer::FindBarycentric(const vec3& ab, const vec3& ac, const vec3& pa)
{
	vec3 u = cross(vec3(ab.y, ac.y, pa.y), vec3(ab.x, ac.x, pa.x));
	//if (u.z < 1) return vec3(-1, -1, -1);
	if (std::abs(u.z) < 1) return vec3(-1.0f, -1.0f, -1.0f);
	return vec3(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

void Renderer::DrawTriangle(vec3 a, vec3 b, vec3 c, const ColorRGB& color)
{
	vec3 ab = b - a;
	vec3 ac = c - a;

	//if (cross(ab, ac))

	vec2i bboxmin(0, 0);
	vec2i bboxmax(m_Width - 1, m_Height - 1);

	bboxmin.x = clamp(min(a.x, min(b.x, c.x)), 0, bboxmax.x);
	bboxmin.y = clamp(min(a.y, min(b.y, c.y)), 0, bboxmax.y);

	bboxmax.x = clamp(max(a.x, max(b.x, c.x)), 0, bboxmax.x);
	bboxmax.y = clamp(max(a.y, max(b.y, c.y)), 0, bboxmax.y);

	vec3 p;

	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
	{
		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
		{
			vec3 barycentric = FindBarycentric(ab, ac, a - p);

			//std::cout << p << std::endl;
			//std::cout << barycentric << std::endl;
			//if (barycentric.x + barycentric.y <= 1)
			if (!(barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0))
			{
				int idx = (p.y * m_Width + p.x);
				p.z = a.z * barycentric.x + b.z * barycentric.y + c.z * barycentric.z;
				if (p.z < m_ZBuffer[idx] && p.z > 0)  // Z test
				{
					m_ZBuffer[idx] = p.z;

					idx *= 3;
					m_FrameBuffer[idx] = color.r;
					m_FrameBuffer[idx + 1] = color.g;
					m_FrameBuffer[idx + 2] = color.b;
				}
			}
		}
	}
}
