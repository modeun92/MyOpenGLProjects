//#include <GL/glew.h>
//#include <iostream>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//namespace texture_modeun {
//	void doTexture() {
//		unsigned int texture;
//		
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		int width, height, nrChannels;
//		unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//
//		if (data) {
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			glGenerateMipmap(GL_TEXTURE_2D);
//		}
//		else {
//			std::cout << "Failed to load texture" << std::endl;
//		}
//		stbi_image_free(data);
//
//
//		unsigned int VAO, VBO;
//		//VERTEX ARRAY OBJECT
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//		//VERTEX BUFFER OBJECT
//		glGenBuffers(1, &VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//		float vertices[] = {
//			// positions		// colors			// texture coords
//			0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
//			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
//			-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
//			-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f, // top left
//		};
//		unsigned int indices[] = {
//			0, 1, 2,
//			0, 2, 3
//		};
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)(6 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//
//	}
//}