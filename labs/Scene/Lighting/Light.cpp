#include "Light.h"

Light::Light()
{
	this->direction.x = 0;
	this->direction.y = 20;
	this->direction.z = 20;
	this->direction.w = 1;
	this->ambient = glm::vec4(0.71, 0.71, 0.71, 1);
	this->diffuse = glm::vec4(0.71, 0.71, 0.71, 1);
	this->specular = glm::vec4(0.0, 0.0, 0.0, 1);
}

void Light::setDirection(glm::vec3& direction)
{
	this->direction.x = direction.x;
	this->direction.y = direction.y;
	this->direction.z = direction.z;
	this->direction.w = 1;
}

void Light::setAmbient(glm::vec4& ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec4& diffuse)
{
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec4& specular)
{
	this->specular = specular;
}

glm::vec4& Light::getDirection()
{
	return this->direction;
}

glm::vec4& Light::getAmbient()
{
	return this->ambient;
}

glm::vec4& Light::getDiffuse()
{
	return this->diffuse;
}

glm::vec4& Light::getSpecular()
{
	return this->specular;
}