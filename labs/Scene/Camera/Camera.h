#pragma once

#include <windows.h>

#include "GL/glew.h"

#include <vector>

#include "GL/freeglut.h"

#include <glm/glm.hpp>

#include "../Object/GraphicObject/GraphicObject.h"

// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// конструкторы
	Camera();
	Camera(vec3, vec3, vec3);
	// установить матрицу проекции
	void setProjectionMatrix(float fovy, float aspect, float zNear, float zFar);
	// получить матрицу проекции
	glm::mat4& getProjectionMatrix();
	// получить матрицу вида
	glm::mat4& getViewMatrix();
	// передвинуть камеру и точку наблюдения в горизонтальной плоскости (OXZ)
	void moveOXZ(float dx, float dz);
	// повернуть в горизонтальной и вертикальной плоскости (угол задается в градусах)
	void rotate(float horizAngle, float vertAngle);
	// приблизить/удалить камеру к/от точки наблюдения
	void zoom(float dR);
	//получить камеру
	vec3 getCameraPosition();

private:
	// пересчитать матрицу вида
	void recalculateViewMatrix();
	//функция для перевода декартовых координат в полярные
	void fromDecToPolar();
private:
	// необходимые приватные поля класса
	// генерируем матрицу проекции
	mat4 projectionMatrix;
	// матрица вида
	mat4 viewMatrix;
	// позиция камеры - (0, 3, 5)
	vec3 eye;
	// точка, в которую направлена камера - (0, 0, 0);
	vec3 center;
	// примерный вектор "вверх" (0, 1, 0)
	vec3 up;
	// углы поворота камеры и радиус( для декартовых координат )
	float angleX;
	float angleY;
	float r;
};