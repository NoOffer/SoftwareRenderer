#pragma once

#include <utility>
#include <functional>
#include <time.h>

#include "core/core.h"
#include "shader/blinn_phong.h"

class Renderer
{
public:
	Renderer(int width, int height, Camera* cam);
	~Renderer();

	void ClearBuffer();
	void Draw(Model& model);
	unsigned char const* GetFrameBuffer();

	inline double GetDeltaTime() { return m_DeltaTime; }

private:
	void DrawLine(int x0, int y0, int x1, int y1, const ColorRGB& color);
	void DrawLine(vec2i x, vec2i y, const ColorRGB& color);

	vec3 FindBarycentric(const vec3& ab, const vec3& ac, const vec3& pa);
	//void DrawTriangle(vec3 a, vec3 b, vec3 c, const ColorRGB& color);
	void DrawTriangle(v2f i1, v2f i2, v2f i3, ColorRGB(*Frag)(v2f));

	int            m_Width, m_Height;
	unsigned char* m_FrameBuffer;
	float*         m_ZBuffer;

	Camera*		   m_Camera;

	int            m_CurrentTimeMS;
	double         m_DeltaTime;
};
