#pragma once
#include <windows.h>
#include "stdio.h"
#include <string>
#include <fstream>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	// �������� ������� �� ������� ������
	bool load(std::string veftexShaderFilename, std::string fragmentShaderFilename);

	// ����� ������� � �������� ��������
	void activate();

	// ���������� �������
	static void deactivate();

private:
	// �������� ���������� ������� ���������� ���� � �������� ��������� ������ ������� �� ���������� �����
	GLuint createShaderObject(GLenum shaderType, std::string filename);

private:
	// ��������� ��������� (������)
	GLuint	program;
};
