#include "GraphicObject.h"


GraphicObject::GraphicObject()
{
	meshId = {};
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

void GraphicObject::setMeshId(int id)
{
	this->meshId = id;
}

void GraphicObject::setTextureId(int id)
{
	this->textureId = id;
}

vec4& GraphicObject::getColor()
{
	return color;
}

mat4& GraphicObject::getModelMatrix()
{
	return modelMatrix;
}

int GraphicObject::getTextureId()
{
	return textureId;
}

int GraphicObject::getMeshId()
{
	return meshId;
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = mat4(
		vec4(cos(angle), 0, sin(angle), 0),	// 1-ый столбец: направление оси X
		vec4(0, 1, 0, 0), // 2-ой столбец: направление оси Y
		vec4(-sin(angle), 0, cos(angle), 0), // 3-ий столбец: направление оси Z
		vec4(position.x, position.y, position.z, 1) // 4-ый столбец: позиция объекта (начала координат)
	);
}