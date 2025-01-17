#include "GlewfwConfig.cpp"
#include "GlmConfig.cpp"

float vertices[] = {
	//x		y		z			x		y
	-0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	-0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	-0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,

	-0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	1.0f,

	-0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	1.0f,
	-0.5f,	0.5f,	-0.5f,		1.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		1.0f,	1.0f,

	0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	0.5f,	-0.5f,	0.5f,		0.0f,	1.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	1.0f,

	-0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	-0.5f,		1.0f,	0.0f,
	0.5f,	-0.5f,	0.5f,		1.0f,	1.0f,

	-0.5f,	0.5f,	-0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		0.0f,	1.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	1.0f,
};
unsigned int indices[] {
	0, 1, 2,
	1, 2, 3 
};
void RotateModelByTime(glm::mat4 &model) {
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
		glm::vec3(0.5f, 1.0f, 0.0f));
}

void Dodo() {
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);															// 3. Vertex Array Object for both
	glGenBuffers(1, &VBO);																// 4. Vertex Buffer Object for vertices
	glGenBuffers(1, &EBO);																// 5. Element Buffer Object for indices

	glBindVertexArray(VAO);																// 6. binding Vertex Array Object

	glBindBuffer(GL_ARRAY_BUFFER, VBO);													// 7-1. binding Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// 7-2. buffering vertices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);											// 8-1. binding Element Buffer Object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// 8-2. buffering indices

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}