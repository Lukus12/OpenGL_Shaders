#include "Camera.h"
#define CORRECTION 3.14159265 / 180
Camera::Camera()
{
}

Camera::Camera(vec3 eye, vec3 center, vec3 up)
{
	//берЄм шаблон из dispay-€
	this->eye = eye;
	this->center = center;
	this->up = up;
	viewMatrix = lookAt(eye, center, up);
	//заполн€ем углы
	fromDecToPolar();
}

void Camera::setProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	// формируем матрицу проекции
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
	vec3 forward = center - eye; // вектор направлени€ камеры
	vec3 right = cross(forward, up); // Ќаходим вектор "вправо"

	eye += right * dx; // ѕеремещаем камеру вправо/влево
	eye += up * dz; // ѕеремещаем камеру вверх/вниз

	center = eye + forward; // ќбновл€ем точку наблюдени€
	recalculateViewMatrix(); // ѕересчитываем матрицу вида
}

void Camera::rotate(float horizAngle, float vertAngle)
{
	//горизонтальна€ плоскость
	angleX += horizAngle;
	if (angleX >= 180) angleX -= 360;
	if (angleX <= -180) angleX += 360;
	//вертикальна€ плоскость
	angleY -= vertAngle;
	if (angleY < 5) angleY = 5;
	if (angleY > 89.9) angleY = 89.9;
	//преобразовываем в декартовые координаты, как в лабах прошлого семестра
	float r = length(eye - center);
	eye.x = r * sin(angleY * CORRECTION) * cos(angleX * CORRECTION);
	eye.z = r * sin(angleY * CORRECTION) * sin(angleX * CORRECTION);
	eye.y = r * cos(angleY * CORRECTION);
	//Press F, чтобы отдать честь —ане, который пожертвовал собой, чтобы найти здесь проблему
	eye += center;
	viewMatrix = lookAt(eye, center, up);
}

void Camera::zoom(float dR)
{
	vec3 forward = center - eye; // Ќормализуем вектор направлени€ камеры
	eye += forward * dR; // ѕриближаем/удал€ем камеру от точки наблюдени€
	recalculateViewMatrix();
}

void Camera::recalculateViewMatrix()
{
	//находим пол€рные координаты
	fromDecToPolar();
	viewMatrix = lookAt(eye, center, up); // ќбновл€ем матрицу вида
}

//находим пол€рные координаты
void Camera::fromDecToPolar()
{
	vec3 v1 = eye - center;
	vec3 v2 = vec3(v1.x, 0, v1.z);

	//считаем углы
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = 90 - degrees(acos(cos_y));

	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));

	if (v1.z < 0) {
		angleX = -angleX;
	}
}