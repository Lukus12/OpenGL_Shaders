#include "PhongMaterialWithTexture.h"

using namespace std;
using namespace rapidjson;


void PhongMaterialWithTexture::setAmbient(vec4 color)
{
	this->ambient.r = color.x;
	this->ambient.g = color.y;
	this->ambient.b = color.z;
	this->ambient.a = 1;
}

void PhongMaterialWithTexture::setDiffuse(vec4 color)
{
	this->diffuse.r = color.x;
	this->diffuse.g = color.y;
	this->diffuse.b = color.z;
	this->diffuse.a = 1;
}

void PhongMaterialWithTexture::setSpecular(vec4 color)
{
	this->specular.r = color.x;
	this->specular.g = color.y;
	this->specular.b = color.z;
	this->specular.a = 1;
}

void PhongMaterialWithTexture::setEmission(vec4 color)
{
	this->emission.r = color.x;
	this->emission.g = color.y;
	this->emission.b = color.z;
	this->emission.a = 1;
}

void PhongMaterialWithTexture::setShininess(float p)
{
	this->shininess = p;
}

void PhongMaterialWithTexture::setTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
}


void PhongMaterialWithTexture::load(string filename) {
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open()) {
		cout << "Failed!\n";
	}
	else {
		//cout << "Fail Open!\n";
		int j = 0;
		string str;
		vec4 color{};
		float value;
		string simbol = "";

		while (getline(fin, str)) {
			istringstream strNew(str);
			string view;

			strNew >> view;
			if (view != "shininess:") {
				strNew >> color[0] >> color[1] >> color[2];
				if (view == "diffuse:") {
					setDiffuse(color);
				}
				if (view == "ambient:") {
					setAmbient(color);
				}
				if (view == "specular:") {
					setSpecular(color);
				}
				if (view == "emission:") {
					setEmission(color);
				}
				color = {};
			}
			if (view == "shininess:") {
				strNew >> value;
				setShininess(value);
				value = {};
			}
		}

	}
	fin.close();
}

void PhongMaterialWithTexture::load(MaterialParams value)
{
	setDiffuse(value.Diffuse);
	setAmbient(value.Ambient);
	setSpecular(value.Specular);
	setEmission(value.Emission);
	setShininess(value.Shininess);
}


void PhongMaterialWithTexture::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient)); //Фоновая отражающая способность материала. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse)); //Диффузная отражающая способность
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular)); //Зеркальная отражающая способность
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission)); //Цвет самосвечения. 
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //Степень отполированности объекта

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	(*texture).apply();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}