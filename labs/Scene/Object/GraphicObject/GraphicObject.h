#pragma once

#include "../../General_Heading.h"

using namespace std;
using namespace glm;

// ����� ��� ������ � ����������� ��������
class GraphicObject
{
public:
	// ����������� �� ���������
	GraphicObject();
	// ���������� ���� �������
	void setColor(vec4 color);
	// ���������� ������� �������
	void setPosition(vec3 position);
	// ���������� ���� �������� � �������� ������������ ��� OY �� ������� �������
	void setAngle(float degree);
	// ���������� ������������� ������������� ����
	void setMeshId(int id);

	// �������� ��������� ���������
	vec4& getColor();
	mat4& getModelMatrix();
	int getMeshId();
private:
	// ������������� ������������� ����
	int meshId;
	// ���� �������
	vec4 color = {};
	// ������� ������ (������ ������� � ����������)
	mat4 modelMatrix;
	// ���� ��������
	float angle;
	//������� � ���������� �����������
	vec3 position = {};
	//���������� ������ ������� �� ��������� �� ���� � ���������
	void recalculateModelMatrix();
};
