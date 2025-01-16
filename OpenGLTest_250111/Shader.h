#pragma once

#ifndef GLEW_STATICC
#define GLEW_STATICC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
class Shader {
public:
	Shader(const char*, const char*);
	void Dispose();
	void Use();
	void SetBool(const string&, bool) const;
	void SetInt(const string&, int) const;
	void SetFloat(const string&, float) const;
  void Shader::SetMat4(const string&, glm::mat4) const;
private:
	unsigned int m_Id;
	unsigned int GenerateShader(const char*, int);
};