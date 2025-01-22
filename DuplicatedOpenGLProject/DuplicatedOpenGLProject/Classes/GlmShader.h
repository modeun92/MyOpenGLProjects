#pragma once
#include "Shader.h"
#include "GlmConfig.h"

class GlmShader : public Shader
{
public:
	GlmShader(const char* a_VertexPath, const char* a_FragmentPath) : Shader(a_VertexPath, a_FragmentPath) {}
	void SetMat4(const string&, glm::mat4) const;
};