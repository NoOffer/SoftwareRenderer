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

	float specular = max(0.0f, dot(i.normalWS, h));

	return ColorRGB{ 255, 255, 255 } *i.vertexWS.xyz();
	return ColorRGB{ 255, 255, 255 } *(specular + diffuse + 0.03f);
}
