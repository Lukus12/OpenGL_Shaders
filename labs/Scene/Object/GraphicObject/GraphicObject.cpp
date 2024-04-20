#include "GraphicObject.h"


GraphicObject::GraphicObject()
{
	angle = 0;
	modelMatrix = mat4(
		vec4(1, 0, 0, 0),	// 1-ый столбец: направление оси X
		vec4(0, 1, 0, 0),	// 2-ой столбец: направление оси Y
		vec4(0, 0, 1, 0),	// 3-ий столбец: направление оси Z
		vec4(0, 0, 0, 1));	// 4-ый столбец: позиция объекта (начала координат)
}

void GraphicObject::setColor(vec4 color)
{
	this->color = color;
}

void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
	recalculateModelMatrix();
}

void GraphicObject::setAngle(float degree)
{
	angle = degree / 180 * 3.1415;
	recalculateModelMatrix();
}

vec4& GraphicObject::getColor()
{
	return color;
}

mat4& GraphicObject::getModelMatrix()
{
	return modelMatrix;
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix() {
	mat4 trans = translate(mat4(1.0f), position);
	mat4 rot = trans * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), -position);
	mat4 scal = scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));

	modelMatrix = scal * rot * trans;
}