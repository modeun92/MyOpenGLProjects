#pragma once
#include "GlewfwConfig.cpp"
#include "GlmConfig.cpp"
#include "StbImageConfig.h"
#include <iostream>
namespace cube {
	static float vertices[] = {
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

	static unsigned int indices[]{
		0, 1, 2,
		1, 2, 3
	};

	static void RotateModelByTime(glm::mat4& model) {
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(1.0f),
			glm::vec3(0.1f, 0.2f, 0.0f));
	}

	static void BindObjects(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {
		glGenVertexArrays(1, &VAO);															// 3. Vertex Array Object for both
		glGenBuffers(1, &VBO);																// 4. Vertex Buffer Object for vertices
		//glGenBuffers(1, &EBO);																// 5. Element Buffer Object for indices
															// 6. binding Vertex Array Object

		glBindBuffer(GL_ARRAY_BUFFER, VBO);													// 7-1. binding Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// 7-2. buffering vertices

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);											// 8-1. binding Element Buffer Object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// 8-2. buffering indices

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	static void GenerateTexture(const char* a_Path, unsigned int& a_Id) {
		// ---------
		glGenTextures(1, &a_Id);
		glBindTexture(GL_TEXTURE_2D, a_Id);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char* data = stbi_load(a_Path, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	static void DeleteObjects(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		//glDeleteBuffers(1, &EBO);
	}
}