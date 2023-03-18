#include "Renderer.h"

Renderer::Renderer(int width, int height, Camera* cam) : m_Width(width), m_Height(height), m_Camera(cam), m_DeltaTime(0)
{
	m_FrameBuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 3);
	if (m_FrameBuffer) memset(m_FrameBuffer, 0, sizeof(unsigned char) * width * height * 3);

	m_ZBuffer = (float*)malloc(sizeof(float) * width * height);
	if (m_ZBuffer) for (int i = 0; i < width * height; i++) m_ZBuffer[i] = 1.0f;

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
	for (int i = 0; i < m_Width * m_Height; i++) m_ZBuffer[i] = 1.0f;
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
	BlinnPhongShader::SetViewMatrix((*m_Camera).GetViewMatrix());
	BlinnPhongShader::SetProjMatrix((*m_Camera).GetProjMatrix());
	BlinnPhongShader::SetLightPos(vec3(0.0f, 5.0f, 0.0f));
	BlinnPhongShader::SetCamPos((*m_Camera).GetPosition());

	VertexBuffer& vb = model.GetVertexBuffer();
	IndexBuffer& ib = model.GetIndexBuffer();

	for (int i = 0; i < ib.GetCount(); i += 3)
	{
		a2v o1 = { vec4(vb[ib[i]], 1.0f) };
		a2v o2 = { vec4(vb[ib[i + 1]], 1.0f) };
		a2v o3 = { vec4(vb[ib[i + 2]], 1.0f) };
		DrawTriangle(
			BlinnPhongShader::Vert(o1),
			BlinnPhongShader::Vert(o2),
			BlinnPhongShader::Vert(o3),
			BlinnPhongShader::Frag);
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

/* Caution:: Wrong Interpolation */
//void Renderer::DrawTriangle(vec3 a, vec3 b, vec3 c, const ColorRGB& color)
//{
//	vec3 ab = b - a;
//	vec3 ac = c - a;
//
//	//if (cross(ab, ac))
//
//	vec2i bboxmin(0, 0);
//	vec2i bboxmax(m_Width - 1, m_Height - 1);
//
//	bboxmin.x = clamp(min(a.x, min(b.x, c.x)), 0, bboxmax.x);
//	bboxmin.y = clamp(min(a.y, min(b.y, c.y)), 0, bboxmax.y);
//
//	bboxmax.x = clamp(max(a.x, max(b.x, c.x)), 0, bboxmax.x);
//	bboxmax.y = clamp(max(a.y, max(b.y, c.y)), 0, bboxmax.y);
//
//	vec3 p;
//
//	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
//	{
//		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
//		{
//			vec3 barycentric = FindBarycentric(ab, ac, a - p);
//
//			//std::cout << p << std::endl;
//			//std::cout << barycentric << std::endl;
//			//if (barycentric.x + barycentric.y <= 1)
//			if (!(barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0))
//			{
//				int idx = (p.y * m_Width + p.x);
//				p.z = a.z * barycentric.x + b.z * barycentric.y + c.z * barycentric.z;
//				if (p.z < m_ZBuffer[idx] && p.z > 0)  // Z test
//				{
//					m_ZBuffer[idx] = p.z;
//
//					idx *= 3;
//					m_FrameBuffer[idx] = (unsigned char)(255 * p.z * 5);
//					m_FrameBuffer[idx + 1] = (unsigned char)(255 * p.z * 5);
//					m_FrameBuffer[idx + 2] = (unsigned char)(255 * p.z * 5);
//					//m_FrameBuffer[idx] = color.r;
//					//m_FrameBuffer[idx + 1] = color.g;
//					//m_FrameBuffer[idx + 2] = color.b;
//				}
//			}
//		}
//	}
//}

void Renderer::DrawTriangle(v2f i1, v2f i2, v2f i3, ColorRGB(*Frag)(v2f))
{
	vec4 a = i1.vertexCS;
	vec4 b = i2.vertexCS;
	vec4 c = i3.vertexCS;

	//if (cross(ab, ac))

	vec2i bboxmin(0, 0);
	vec2i bboxmax(m_Width - 1, m_Height - 1);

	bboxmin.x = clamp(min(a.x, min(b.x, c.x)), 0, bboxmax.x);
	bboxmin.y = clamp(min(a.y, min(b.y, c.y)), 0, bboxmax.y);

	bboxmax.x = clamp(max(a.x, max(b.x, c.x)), 0, bboxmax.x);
	bboxmax.y = clamp(max(a.y, max(b.y, c.y)), 0, bboxmax.y);

	/* Pre-calculated attribute(s) */
	vec3 normalWS = normalize(cross((i3.vertexWS - i1.vertexWS).xyz(), (i2.vertexWS - i1.vertexWS).xyz()));

	vec3 p;
	float dxAB = a.y - b.y, dxBC = b.y - c.y, dxCA = c.y - a.y;
	float dyAB = b.x - a.x, dyBC = c.x - b.x, dyCA = a.x - c.x;
	float cAB = a.x * b.y - b.x * a.y, cBC = b.x * c.y - c.x * b.y, cCA = c.x * a.y - a.x * c.y;

	float fTempAB = dxAB * bboxmin.x + dyAB * bboxmin.y + cAB;
	float fTempBC = dxBC * bboxmin.x + dyBC * bboxmin.y + cBC;
	float fTempCA = dxCA * bboxmin.x + dyCA * bboxmin.y + cCA;
	for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
	{
		float fAB = fTempAB, fBC = fTempBC, fCA = fTempCA;
		for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
		{
			//vec3 ab = b - a;
			//vec3 ac = c - a;
			//vec3 barycentric = FindBarycentric(ab, ac, a - p);

			//if (!(barycentric.x < 0 || barycentric.y < 0 || barycentric.z < 0))  // Check if a pixel is in the triangle
			if (!(fAB < 0 || fBC < 0 || fCA < 0))  // Check if a pixel is in the triangle
			{
				float s2 = fAB + fBC + fCA;
				vec3 barycentric(fBC / s2, fCA / s2, fAB / s2);

				//Interpolate p.z, valid in [1.0f, 0.5f]
				//The value of p.z is actually 1/Z
				float azFactor = barycentric.x / a.w, bzFactor = barycentric.y / b.w, czFactor = barycentric.z / c.w;
				float rawW = azFactor + bzFactor + czFactor;
				p.z = (azFactor * a.z + bzFactor * b.z + czFactor * c.z) / rawW;
				//Log(p.z);

				int idx = (p.y * m_Width + p.x);
				if (p.z >= 0.0f && p.z < m_ZBuffer[idx])  // Z test
				{
					m_ZBuffer[idx] = p.z;

					v2f i;
					i.normalWS = normalWS;
					i.vertexWS = (azFactor * i1.vertexWS + bzFactor * i2.vertexWS + czFactor * i3.vertexWS) / rawW;
					ColorRGB color = Frag(i);

					idx *= 3;
					//m_FrameBuffer[idx] = 255 * (1 / p.z - 1);
					//m_FrameBuffer[idx + 1] = 255 * (1 / p.z - 1);
					//m_FrameBuffer[idx + 2] = 255 * (1 / p.z - 1);
					m_FrameBuffer[idx] = color.r;
					m_FrameBuffer[idx + 1] = color.g;
					m_FrameBuffer[idx + 2] = color.b;
				}
			}
			fAB += dxAB; fBC += dxBC; fCA += dxCA;
		}
		fTempAB += dyAB; fTempBC += dyBC; fTempCA += dyCA;
	}

}
