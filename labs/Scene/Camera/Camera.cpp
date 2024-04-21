#include "Camera.h"
#define CORRECTION 3.14159265 / 180
Camera::Camera()
{
}

Camera::Camera(vec3 eye, vec3 center, vec3 up)
{
	//���� ������ �� dispay-�
	this->eye = eye;
	this->center = center;
	this->up = up;
	viewMatrix = lookAt(eye, center, up);
	//��������� ����
	fromDecToPolar();
}

void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	// ��������� ������� ��������
	projectionMatrix = perspective(radians(fovy), aspect, zNear, zFar);

}

mat4& Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

mat4& Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::moveOXZ(float dx, float dz)
{
	vec3 forward = center - eye; // ������ ����������� ������
	vec3 right = cross(forward, up); // ������� ������ "������"

	eye += right * dx; // ���������� ������ ������/�����
	eye += up * dz; // ���������� ������ �����/����

	center = eye + forward; // ��������� ����� ����������
	recalculateViewMatrix(); // ������������� ������� ����
}

void Camera::rotate(float horizAngle, float vertAngle)
{
	//�������������� ���������
	angleX += horizAngle;
	if (angleX >= 180) angleX -= 360;
	if (angleX <= -180) angleX += 360;
	//������������ ���������
	angleY -= vertAngle;
	if (angleY < 5) angleY = 5;
	if (angleY > 89.9) angleY = 89.9;
	//��������������� � ���������� ����������, ��� � ����� �������� ��������
	float r = length(eye - center);
	eye.x = r * sin(angleY * CORRECTION) * cos(angleX * CORRECTION);
	eye.z = r * sin(angleY * CORRECTION) * sin(angleX * CORRECTION);
	eye.y = r * cos(angleY * CORRECTION);
	//Press F, ����� ������ ����� ����, ������� ����������� �����, ����� ����� ����� ��������
	eye += center;
	viewMatrix = lookAt(eye, center, up);
}

void Camera::zoom(float dR)
{
	vec3 forward = center - eye; // ����������� ������ ����������� ������
	eye += forward * dR; // ����������/������� ������ �� ����� ����������
	recalculateViewMatrix();
}

void Camera::recalculateViewMatrix()
{
	//������� �������� ����������
	fromDecToPolar();
	viewMatrix = lookAt(eye, center, up); // ��������� ������� ����
}

//������� �������� ����������
void Camera::fromDecToPolar()
{
	vec3 v1 = eye - center;
	vec3 v2 = vec3(v1.x, 0, v1.z);

	//������� ����
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = 90 - degrees(acos(cos_y));

	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));

	if (v1.z < 0) {
		angleX = -angleX;
	}
}