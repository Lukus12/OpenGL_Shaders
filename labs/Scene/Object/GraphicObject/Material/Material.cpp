#include "Material.h"

Material::Material() {}

bool Material::loadFromJson(std::string filename)
{
	std::fstream File(filename);
	if (!File) {
		std::cout << "Ошибка при октрытии файла материала!\n";
		return false;
	}

	std::string line;
	getline(File, line, static_cast<char>(0));
	File.close();

	rapidjson::Document document;
	document.Parse(line.c_str());
	if (document.GetParseError() != 0) {
		std::cout << filename << "Ошибка парсера!\n";
		return false;
	}

	if (document.HasMember("ambient")) {
		auto array = document["ambient"].GetArray();
		for (int i = 0; i < 4; i++) {
			ambient[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("diffuse")) {
		auto array = document["diffuse"].GetArray();
		for (int i = 0; i < 4; i++) {
			diffuse[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("specular")) {
		auto array = document["specular"].GetArray();
		for (int i = 0; i < 4; i++) {
			specular[i] = array[i].GetFloat();
		}
	}
	if (document.HasMember("shineness")) {
		shininess = document["shininess"].GetFloat();
	}
}

glm::vec4& Material::getAmbient()
{
	return ambient;
}

glm::vec4& Material::getDiffuse()
{
	return diffuse;
}

glm::vec4& Material::getSpecular()
{
	return specular;
}

float Material::getShininess()
{
	return shininess;
}