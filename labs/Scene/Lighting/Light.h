#pragma once

#include <windows.h>

#include "GL/glew.h"

#include <vector>

#include "GL/freeglut.h"

#include <glm/glm.hpp>

#include "..\Object\GraphicObject\GraphicObject.h"

// ����� ��� ������ � ���������� �����
class Light
{
public:
	// ������������
	Light();
	Light(vec3 position);
	Light(float x, float y, float z);
	// ������� ��������� ���������� ��������� �����
	void setPosition(vec3 position);
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	// ��������� ���� ���������� ��������� ����� � �������� �������
	// ������ ������� ������ ���������� ����� ��������� ������,
	// �.�. ����� ��������������� ������� ��������� �����
	void apply(GLenum LightNumber = GL_LIGHT0);
private:
	// ������� ��������� �����
	vec4 position;
	// ������� ������������ ��������� �����
	vec4 ambient;
	// ��������� ������������
	vec4 diffuse;
	// ���������� ������������
	vec4 specular;
};