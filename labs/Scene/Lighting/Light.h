#pragma once

#include "../../General_Heading.h"

using namespace glm;

// ����� ��� ������ � ���������� �����
class Light
{
public:
	// ������������
	Light();

	// ������� ��������� ���������� ��������� �����
	void setDirection(glm::vec3& direction);
	void setAmbient(glm::vec4& ambient);
	void setDiffuse(glm::vec4& diffuse);
	void setSpecular(glm::vec4& specular);
	
	// ��������� ��������� ���������� ��������� �����
	glm::vec4& getDirection();
	glm::vec4& getAmbient();
	glm::vec4& getDiffuse();
	glm::vec4& getSpecular();
private:
	// ������� ��������� �����
	glm::vec4 direction;
	// ������� ������������ ��������� �����
	glm::vec4 ambient;
	// ��������� ������������
	glm::vec4 diffuse;
	// ���������� ������������
	glm::vec4 specular;
};