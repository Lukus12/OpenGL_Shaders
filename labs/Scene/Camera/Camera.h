#pragma once

#include <windows.h>

#include "GL/glew.h"

#include <vector>

#include "GL/freeglut.h"

#include <glm/glm.hpp>

#include "../Object/GraphicObject/GraphicObject.h"

// ����� ��� ������ � �������
class Camera
{
public:
	// ������������
	Camera();
	Camera(vec3, vec3, vec3);
	// ���������� ������� ��������
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
	// �������� ������� ��������
	glm::mat4& getProjectionMatrix();
	// �������� ������� ����
	glm::mat4& getViewMatrix();
	// ����������� ������ � ����� ���������� � �������������� ��������� (OXZ)
	void moveOXZ(float dx, float dz);
	// ��������� � �������������� � ������������ ��������� (���� �������� � ��������)
	void rotate(float horizAngle, float vertAngle);
	// ����������/������� ������ �/�� ����� ����������
	void zoom(float dR);
	//�������� ������
	vec3 getCameraPosition();

private:
	// ����������� ������� ����
	void recalculateViewMatrix();
	//������� ��� �������� ���������� ��������� � ��������
	void fromDecToPolar();
private:
	// ����������� ��������� ���� ������
	// ���������� ������� ��������
	mat4 projectionMatrix;
	// ������� ����
	mat4 viewMatrix;
	// ������� ������ - (0, 3, 5)
	vec3 eye;
	// �����, � ������� ���������� ������ - (0, 0, 0);
	vec3 center;
	// ��������� ������ "�����" (0, 1, 0)
	vec3 up;
	// ���� �������� ������ � ������( ��� ���������� ��������� )
	float angleX;
	float angleY;
	float r;
};