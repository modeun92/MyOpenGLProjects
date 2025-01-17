#pragma once
#include "GlmShader.h"

class GlmMvpShader : public GlmShader
{
public:
	void SetModel(glm::mat4) const;
	void SetView(glm::mat4) const;
	void SetProjection(glm::mat4) const;
	void SetMvp(glm::mat4, glm::mat4, glm::mat4) const;
protected:
	const string MODEL = "model";
	const string VIEW = "view";
	const string PROJECTION = "projection";
};