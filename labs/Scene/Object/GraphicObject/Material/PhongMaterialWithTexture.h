#pragma once

#include "../../General_Heading.h"

#include <thread>
#include <string>
#include <vector>

#include "rapidjson/document.h"

#include "Material.h"
#include "MaterialParams.h"

using namespace glm;
using namespace std;

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterialWithTexture : public Material
{
public:
	// конструктор по умолчанию
	// 
	//PhongMaterial(string filename, int flag);
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	void load(MaterialParams value);
	//установка текстур
	void setTexture(shared_ptr<Texture> texture);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая 
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
	// текстуры
	shared_ptr<Texture> texture;
};