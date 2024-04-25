#include "Data.h"

Shader shader;

LARGE_INTEGER previous, frequency;

// ������������ ������
Camera camera(vec3(-10.0, 14.0, 30.0), vec3(0, 0, 5), vec3(0, 1, 0));
// ������ ����������� �������� ��� ������ �� �����
vector<GraphicObject> graphicObjects;

//������� �������
POINT lastCursorPos;

void initGraphicObjects()
{
	// ������ �� �������� �������� (��� ��������)
	ResourceManager& rm = ResourceManager::instance();
	// ��������� ���������� ��� �������� ��������������� ����
	int meshId = -1;
	// ��������� ���������� ��� ������������� ������������ �������
	GraphicObject graphicObject;
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//buildings//house_2.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.2, 0.2, 0.2, 1));
	graphicObject.setPosition(vec3(0, 0, 0));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//natures//big_tree.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//natures//big_tree.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.2, 0.8, 0.2, 1));
	graphicObject.setPosition(vec3(-7.5, -0.75, 2.5));
	graphicObject.setAngle(0.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//vehicles//police_car.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.2, 0.2, 1.0, 1));
	graphicObject.setPosition(vec3(+4.5, -2.15, +6.5));
	graphicObject.setAngle(-115.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//vehicles//police_car.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.23, 0.23, 1.0, 1));
	graphicObject.setPosition(vec3(+4.25, -2.15, +10.5));
	graphicObject.setAngle(+105.0);
	graphicObjects.push_back(graphicObject);
	// ���������� ������������ �������
	meshId = rm.loadMesh("Data//MESHES//vehicles//jeep.obj");
	graphicObject.setMeshId(meshId);
	graphicObject.setColor(vec4(0.95, 0.13, 0.13, 1));
	graphicObject.setPosition(vec3(-1.25, -2.15, +9.0));
	graphicObject.setAngle(+170.0);
	graphicObjects.push_back(graphicObject);
}


void init() {
	// �������� �������
	shader.load("Data//SHADER//Example.vsh", "Data//SHADER/Example.fsh");

	//��������� ��������� ������
	camera.setProjectionMatrix(35.0, 800.0 / 600.0, 1.0, 100.0);

	//���������� ������������ ��������
	initGraphicObjects();
	//��������� �������������� �������
	GetCursorPos(&lastCursorPos);
}