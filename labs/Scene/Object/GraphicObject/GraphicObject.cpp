#include "GraphicObject.h"


GraphicObject::GraphicObject()
{
	angle = 0;
	modelMatrix = mat4(
		vec4(1, 0, 0, 0),	// 1-�� �������: ����������� ��� X
		vec4(0, 1, 0, 0),	// 2-�� �������: ����������� ��� Y
		vec4(0, 0, 1, 0),	// 3-�� �������: ����������� ��� Z
		vec4(0, 0, 0, 1));	// 4-�� �������: ������� ������� (������ ���������)
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

// ������ ������� modelMatrix �� ������ position � angle
void GraphicObject::recalculateModelMatrix() {
	mat4 trans = translate(mat4(1.0f), position);
	mat4 rot = trans * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), -position);
	mat4 scal = scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));

	modelMatrix = scal * rot * trans;
}