#pragma once
#include "Shader.h"
#include "GlmConfig.cpp"

class GlmShader : public Shader
{
public:
	void SetMat4(const string&, glm::mat4) const;
};