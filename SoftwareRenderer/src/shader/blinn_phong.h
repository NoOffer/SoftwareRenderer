#pragma once

#include "core/matrix.h"
#include "core/color.h"

struct a2v
{
	vec4 vertexOS;
};

struct v2f
{
	vec4 vertexWS;
	vec4 vertexCS;
	vec3 normalWS;
};

class BlinnPhongShader
{
public:
	inline static void SetViewMatrix(mat4 m) { m_ViewMatrix = m; }
	inline static void SetProjMatrix(mat4 m) { m_ProjMatrix = m; }
	inline static void SetLightPos(vec3 pos) { m_LightPosWS = pos; }
	inline static void SetCamPos(vec3 pos) { m_CamPosWS = pos; }

	static v2f      Vert(a2v i);
	static ColorRGB Frag(v2f i);
private:
	BlinnPhongShader() {}
	~BlinnPhongShader() {}

	static mat4 m_ViewMatrix;
	static mat4 m_ProjMatrix;
	static vec3 m_LightPosWS;
	static vec3 m_CamPosWS;
};

