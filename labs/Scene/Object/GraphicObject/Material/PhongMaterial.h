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

// ����� ��� ������ � ����������
class PhongMaterial : public Material
{
public:
	// ����������� �� ���������
	// 
	//PhongMaterial(string filename, int flag);
	// ������� ���������� ���������
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// �������� ���������� ��������� �� �������� ���������� �����
	void load(std::string filename);
	void load(MaterialParams value);
	// ��������� ���� ���������� ���������
	void apply();
private:
	// ������� ������������ 
	vec4 ambient;
	// ��������� ������������
	vec4 diffuse;
	// ���������� ������������
	vec4 specular;
	// ������������
	vec4 emission;
	// ������� ����������������
	float shininess;
};