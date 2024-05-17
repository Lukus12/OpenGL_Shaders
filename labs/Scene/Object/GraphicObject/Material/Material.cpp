#include "Material.h"

Material::Material()
{
}


bool Material::loadFromJson(std::string filename)
{
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Fail!\n";
		return false;
	}
	string jsonString;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	// парсим - если ошибка, то выходим
	Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		cout << "Invalid file format!\n";
		return false;
	}

	vec4 valueParamsMaterial = {};

	for (auto& member : document.GetObject()) {
		string nameParamsMaterial = member.name.GetString();
		//cout << nameParamsMaterial << " : ";
		if (member.value.IsArray()) {
			/*cout << member.value[0].GetFloat() << " ";
			cout << member.value[1].GetFloat()<<" ";
			cout << member.value[2].GetFloat()<<" ";
			cout << member.value[3].GetFloat()<<" ";
			cout << endl;*/
			valueParamsMaterial[0] = member.value[0].GetFloat();
			valueParamsMaterial[1] = member.value[1].GetFloat();
			valueParamsMaterial[2] = member.value[2].GetFloat();
			valueParamsMaterial[3] = member.value[3].GetFloat();
			if (nameParamsMaterial == "diffuse") {
				this->diffuse = valueParamsMaterial;
			}
			if (nameParamsMaterial == "ambient") {
				this->ambient = valueParamsMaterial;
			}
			if (nameParamsMaterial == "specular") {
				this->specular = valueParamsMaterial;
			}
		}
		else {
			//cout<< member.value.GetFloat()<<endl;
			this->shininess = member.value.GetFloat();
		}
		valueParamsMaterial = {};
	}

	return true;
}

glm::vec4& Material::getAmbient()
{
	return this->ambient;
}

glm::vec4& Material::getDiffuse()
{
	return this->diffuse;
}

glm::vec4& Material::getSpecular()
{
	return this->specular;
}

float Material::getShininess()
{
	return this->shininess;
}
