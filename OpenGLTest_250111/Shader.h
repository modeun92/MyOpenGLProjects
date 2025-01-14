#pragma once

#ifndef GLEW_STATICC
#define GLEW_STATICC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void dispose();
	void use();
	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;
};