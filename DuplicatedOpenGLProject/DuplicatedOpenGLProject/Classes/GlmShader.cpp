#include "GlmShader.h"

void GlmShader::SetMat4(const string& a_Name, glm::mat4 a_Value) const {
	glUniformMatrix4fv(GetUniformLocation(a_Name), 1, GL_FALSE, glm::value_ptr(a_Value));
}
