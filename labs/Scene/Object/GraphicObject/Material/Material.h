#pragma once

#include "../../../../General_Heading.h"

#include "rapidjson/document.h"


using namespace rapidjson;
using namespace std;
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class Material
{
public:
	// конструктор по умолчанию
	Material();
	// загрузка параметров материала из json-файла
	bool loadFromJson(std::string filename);
	// получение различных параметров материала
	glm::vec4& getAmbient();
	glm::vec4& getDiffuse();
	glm::vec4& getSpecular();
	float getShininess();
private:
	// фоновая составляющая
	glm::vec4 ambient;
	// диффузная составляющая
	glm::vec4 diffuse;
	// зеркальная составляющая
	glm::vec4 specular;
	// степень отполированности
	GLfloat shininess;
};