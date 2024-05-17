#include "Light.h"

Light::Light()
{
}

void Light::setDirection(vec3 direction)
{
	//т.к источник света направленный то 4 значение направления 0
	this->direction = vec4(direction, 0);
}

void Light::setAmbient(vec4 ambient)
{
	this->ambient = ambient;
}

void Light::setDiffuse(vec4 diffuse)
{
	this->diffuse = diffuse;
}

void Light::setSpecular(vec4 specular)
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
