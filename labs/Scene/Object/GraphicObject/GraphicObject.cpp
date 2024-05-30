#include "GraphicObject.h"

GraphicObject::GraphicObject()
{
	modelMatrix = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(0, 0, 0, 1));

	color = vec4(1, 0, 0, 1);
	position = vec3(0, 0, 0);
	dimensions = vec3(0, 0, 0);

	angle = 0;
	meshId = 0;
	textureId = 0;
	materialId = 0;
}

void GraphicObject::setColor(vec4& color)
{
	this->color = color;
}

void GraphicObject::setPosition(vec3& position)
{
	this->position = position;
	modelMatrix[3][0] = position.x;
	modelMatrix[3][1] = position.y;
	modelMatrix[3][2] = position.z;
}

void GraphicObject::setAngle(float degree)
{
	float rad = radians(degree);
	modelMatrix[0][0] = cos(rad);
	modelMatrix[0][2] = sin(rad);
	modelMatrix[2][0] = -sin(rad);
	modelMatrix[2][2] = cos(rad);
}

void GraphicObject::setType(GraphicObjectType type)
{
	this->type = type;
}

void GraphicObject::setDimensions(vec3& dimensions)
{
	this->dimensions = dimensions;
}

void GraphicObject::setMeshId(int id)
{
	meshId = id;
}

void GraphicObject::setTextureId(int id)
{
	textureId = id;
}

void GraphicObject::setMaterialId(int id)
{
	materialId = id;
}

vec4 GraphicObject::getColor()
{
	return color;
}

vec3 GraphicObject::getPosition()
{
	return this->position;
}

float GraphicObject::getAngle()
{
	return this->angle;
}

GraphicObjectType GraphicObject::getType()
{
	return this->type;
}

vec3& GraphicObject::getDimensions()
{
	return this->dimensions;
}

mat4& GraphicObject::getModelMatrix()
{
	return modelMatrix;
}

int GraphicObject::getMeshId()
{
	return meshId;
}

int GraphicObject::getTextureId()
{
	return textureId;
}

int GraphicObject::getMaterialId()
{
	return materialId;
}