#pragma once

#include "GlewfwConfig.cpp"


class Shader {
public:
	Shader(const char*, const char*);
	void Dispose();
	void Use();
	void SetBool(const string&, bool) const;
	void SetInt(const string&, int) const;
	void SetFloat(const string&, float) const;
protected:
	unsigned int m_Id;
	unsigned int GenerateShader(const char*, int) const;
	int GetUniformLocation(const string&) const;
};