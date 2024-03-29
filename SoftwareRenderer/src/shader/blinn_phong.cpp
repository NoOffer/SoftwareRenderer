#include "blinn_phong.h"

mat4 BlinnPhongShader::m_ViewMatrix;
mat4 BlinnPhongShader::m_ProjMatrix;
vec3 BlinnPhongShader::m_LightPosWS;
vec3 BlinnPhongShader::m_CamPosWS;

v2f BlinnPhongShader::Vert(a2v i)
{
	v2f o;
	o.vertexWS = i.vertexOS;
	o.vertexCS = mul(m_ProjMatrix, mul(m_ViewMatrix, i.vertexOS));
	//o.vertexCS = o.vertexCS / std::abs(o.vertexCS.w);
	o.vertexCS.x /= std::abs(o.vertexCS.w);
	o.vertexCS.y /= std::abs(o.vertexCS.w);
	return o;
}

ColorRGB BlinnPhongShader::Frag(v2f i)
{
	vec3 lightDir = normalize(m_LightPosWS - i.vertexWS.xyz());

	float diffuse = max(0.0f, dot(i.normalWS, lightDir));

	vec3 viewDir = normalize(m_CamPosWS - i.vertexWS.xyz());
	vec3 h = normalize(viewDir + lightDir);

	float specular = std::pow(max(0.0f, dot(i.normalWS, h)), 2);

	//return ColorRGB{ 255, 255, 255 } *i.vertexWS.xyz();
	return ColorRGB{ 255, 255, 255 } *(specular * 0.2f + diffuse * 0.6f + 0.2f);
}
