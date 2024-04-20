#include "Light.h"

Light::Light() :Light(vec3()) {

}
Light::Light(vec3 position) {

	setPosition(position);
};
Light::Light(float x, float y, float z) :Light(vec3(x, y, z)) {

}

void Light::setPosition(vec3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
	this->position.w = 1;
}

void Light::setAmbient(vec4 color)
{
	this->ambient.r = color.x;
	this->ambient.g = color.y;
	this->ambient.b = color.z;
	this->ambient.a = 1;
}

void Light::setDiffuse(vec4 color)
{
	this->diffuse.r = color.x;
	this->diffuse.g = color.y;
	this->diffuse.b = color.z;
	this->diffuse.a = 1;
}

void Light::setSpecular(vec4 color)
{
	this->specular.r = color.x;
	this->specular.g = color.y;
	this->specular.b = color.z;
	this->specular.a = 1;
}

void Light::apply(GLenum LightNumber)
{
	setAmbient(vec4(0.1, 0.1, 0.1, 1.0));
	setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
	setSpecular(vec4(1.0, 1.0, 1.0, 1.0));

	glLightfv(LightNumber, GL_POSITION, value_ptr(position));
	glLightfv(LightNumber, GL_AMBIENT, value_ptr(ambient));
	glLightfv(LightNumber, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(LightNumber, GL_SPECULAR, value_ptr(specular));
}