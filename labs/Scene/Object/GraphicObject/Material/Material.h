#pragma once

#include "../../../../General_Heading.h"

#include "rapidjson/document.h"


using namespace rapidjson;
using namespace std;
using namespace glm;

// ����� ��� ������ � ����������
class Material
{
public:
	// ����������� �� ���������
	Material();
	// �������� ���������� ��������� �� json-�����
	bool loadFromJson(std::string filename);
	// ��������� ��������� ���������� ���������
	glm::vec4& getAmbient();
	glm::vec4& getDiffuse();
	glm::vec4& getSpecular();
	float getShininess();
private:
	// ������� ������������
	glm::vec4 ambient;
	// ��������� ������������
	glm::vec4 diffuse;
	// ���������� ������������
	glm::vec4 specular;
	// ������� ����������������
	GLfloat shininess;
};