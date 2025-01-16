#include "Shader.h"

Shader::Shader(const char* a_VertexPath, const char* a_FragmentPath) {
	unsigned int 
		l_VertexShaderId(GenerateShader(a_VertexPath, GL_VERTEX_SHADER)),
		l_FragmentId(GenerateShader(a_FragmentPath, GL_FRAGMENT_SHADER));

	m_Id = glCreateProgram();

	glAttachShader(m_Id, l_VertexShaderId);
	glAttachShader(m_Id, l_FragmentId);

	glLinkProgram(m_Id);

	int l_IsSuccessful;
	char l_Log[512];

	glGetProgramiv(m_Id, GL_LINK_STATUS, &l_IsSuccessful);

	if (!l_IsSuccessful) {
		glGetProgramInfoLog(m_Id, 512, NULL, l_Log);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << l_Log << endl;
	}

	glDeleteShader(l_VertexShaderId);
	glDeleteShader(l_FragmentId);
}
void Shader::Use() {
	glUseProgram(m_Id);
}
void Shader::Dispose() {
	glDeleteProgram(m_Id);
}
void Shader::SetBool(const string& a_Name, bool a_Value) const {
	glUniform1i(glGetUniformLocation(m_Id, a_Name.c_str()), (int)a_Value);
}
void Shader::SetInt(const string& a_Name, int a_Value) const {
	glUniform1i(glGetUniformLocation(m_Id, a_Name.c_str()), a_Value);
}
void Shader::SetFloat(const string& a_Name, float a_Value) const {
	glUniform1f(glGetUniformLocation(m_Id, a_Name.c_str()), a_Value);
}
void Shader::SetMat4(const string& a_Name, glm::mat4 a_Value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, a_Name.c_str()), 1, GL_FALSE, glm::value_ptr(a_Value));
}
unsigned int Shader::GenerateShader(const char* a_ShaderPath, int a_ShaderType) {
	string l_Code;
	ifstream l_File;
	l_File.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		l_File.open(a_ShaderPath);
		stringstream l_Stream;
		l_Stream << l_File.rdbuf();
		l_File.close();
		l_Code = l_Stream.str();
	}
	catch (ifstream::failure l_Exception) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ for the path \"" << a_ShaderPath << "\" => " << l_Exception.what() << endl;
		throw l_Exception;
	}

	const char* l_CharsCode = l_Code.c_str();
	unsigned int l_ShaderId;

	int l_IsSuccessful;
	char l_Log[512];
	l_ShaderId = glCreateShader(a_ShaderType);
	glShaderSource(l_ShaderId, 1, &l_CharsCode, NULL);
	glCompileShader(l_ShaderId);
	glGetShaderiv(l_ShaderId, GL_COMPILE_STATUS, &l_IsSuccessful);

	if (!l_IsSuccessful) {
		glGetShaderInfoLog(l_ShaderId, 512, NULL, l_Log);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \"" << a_ShaderPath << "\"\n" << l_Log << endl;
		throw std::exception();
	}

	return l_ShaderId;
}