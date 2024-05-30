#pragma once

#include "../General_Heading.h"

#include <vector>

#include "rapidjson/document.h"

#include "Camera/Camera.h"
#include "Object/GraphicObject/GraphicObject.h"
#include "Object/GraphicObject/RenderManager/RenderManager.h"


using namespace std;
using namespace glm;

// ����� ��� ������ �� ������
class Scene
{
public:
	// ����������� �� ���������
	Scene();

	// ������������� �����
	// ��������: json-���� � ��������� ������� (�models.json�)
	void init(std::string filename);
	// �������� ����� �� json-�����
	bool loadFromJson(std::string filename);

	// ��������� ������������ ������ (������ �� ���������� ������)
	void setCamera(Camera* camera);
	// ��������� ������������� ��������� ����� (������ �� ���������� ������)
	void setLight(Light* light);

	// ����� ���� ����� (����������� ��������� � RenderManager)
	void draw();

	// ��������� ���������� � ����� ��� �������:
	// [���������� �������� ���������� �� ���������]/[����� ���������� �������� �����]
	std::string getSceneDescription();

private:
	// �������� ������� �� ��� �������������� � json-����� ("models.json")
	GraphicObject createGraphicObject(std::string model);

	// �����������, ����� �� ������ � ����������� �� ��������� �� ����
	bool lodTest(GraphicObject& graphicObject);
	// �����������, �������� �� ������ � ��������� �������� ���������
	bool frustumCullingTest(GraphicObject& graphicObject, mat4&);

	// json-������������� ���� ������� (�� ����� "models.json")
	rapidjson::Document document;

	// ��������� �� ������ (�� ���������� ����������)
	Camera* camera;
	// ��������� �� �������� ����� (�� ���������� ����������)
	Light* light;

	// ��� ����������� �������
	std::vector<GraphicObject> graphicObjects;
	// ���������� - ������� �������� �������� �� ��������� � ������� �����
	int renderedObjectCount;
};