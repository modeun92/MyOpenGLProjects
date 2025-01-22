#pragma once
#include "GlewfwConfig.h"
#include "GlmConfig.h"
#include "ImageConfig.h"
#include <iostream>
namespace cube {
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

	unsigned int indices[]{
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23,
	};

	void RotateModelByTime(glm::mat4& model) {
		model = glm::rotate(model, glm::radians(1.0f),
			glm::vec3(0.1f, 0.3f, 0.2f));
	}

	void BindObjects(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {
		glGenVertexArrays(1, &VAO);															// 3. Vertex Array Object for both
		glGenBuffers(1, &VBO);																// 4. Vertex Buffer Object for vertices
		glGenBuffers(1, &EBO);																// 5. Element Buffer Object for indices
		// 6. binding Vertex Array Object

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);													// 7-1. binding Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// 7-2. buffering vertices

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);											// 8-1. binding Element Buffer Object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// 8-2. buffering indices

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void Draw(const unsigned int& VAO) {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	void Draw() {
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
#if defined STB_IMAGE_IMPLEMENTATION
	void GenerateTexture(const char* a_Path, unsigned int& a_Id) {
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
#elif defined GLI_IMAGE_IMPLEMENTATION
	void GenerateTexture(const char* a_Path, unsigned int& a_Id)
	{
		gli::texture l_Texture = gli::load(a_Path);
		if (l_Texture.empty())
			throw exception();

		gli::gl GL(gli::gl::PROFILE_GL33);
		gli::gl::format const Format = GL.translate(l_Texture.format(), l_Texture.swizzles());
		GLenum Target = GL.translate(l_Texture.target());
		assert(gli::is_compressed(l_Texture.format()) && Target == gli::TARGET_2D);

		glGenTextures(1, &a_Id);
		glBindTexture(Target, a_Id);
		glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(l_Texture.levels() - 1));
		glTexParameteriv(Target, GL_TEXTURE_SWIZZLE_RGBA, &Format.Swizzles[0]);
		auto a = l_Texture.extent();
		glTexStorage2D(Target, static_cast<GLint>(l_Texture.levels()), Format.Internal, a.x, a.y);
		for (std::size_t Level = 0; Level < l_Texture.levels(); ++Level)
		{
			glm::tvec3<GLsizei> Extent(l_Texture.extent(Level));
			glCompressedTexSubImage2D(
				Target, static_cast<GLint>(Level), 0, 0, Extent.x, Extent.y,
				Format.Internal, static_cast<GLsizei>(l_Texture.size(Level)), l_Texture.data(0, 0, Level));
		}
	}
#elif defined DEVIL_IMAGE_IMPLEMENTATION
	void GenerateTexture(const char* a_Path, unsigned int& a_Id)
	{
		ILubyte* Lump;
		ILuint Size;
		FILE* File;

		fopen_s(&File, a_Path, "rb");
		fseek(File, 0, SEEK_END);
		Size = ftell(File);

		Lump = (ILubyte*)malloc(Size);
		fseek(File, 0, SEEK_SET);
		fread(Lump, 1, Size, File);
		fclose(File);

		ilLoadL(IL_JPG, Lump, Size);
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

		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		if (Lump)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 500, 500, 0, GL_RGB, GL_UNSIGNED_BYTE, Lump);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else { std::cout << "Failed to load texture" << std::endl; }
		free(Lump);
	}
#elif defined FREE_IMAGE_IMPLEMENTATION
	void GenerateTexture(const char* a_Path, unsigned int& a_Id) {
		int width, height;
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP* dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(a_Path, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(a_Path);
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			throw exception();

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, a_Path);
		//if the image failed to load, return failure
		if (!dib)
		{
			throw exception();
		}

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (width == 0) || (height == 0))
		{
			throw exception();
		}

		//generate an OpenGL texture ID for this texture
		glGenTextures(1, &a_Id);
		//bind to the new texture ID
		glBindTexture(GL_TEXTURE_2D, a_Id);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		// 
		//store the texture data for OpenGL use
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);

		//Free FreeImage's copy of the data
		FreeImage_Unload(dib);
	}
#endif
	void DeleteTexture(unsigned int& a_Id) {
		glDeleteTextures(1, &a_Id);
	}
	void DeleteObjects(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}