#include "Data.h"

Shader shader;

LARGE_INTEGER previous, frequency;

// ������������ ������
Camera camera(vec3(0.0, 4.0, 8.0), vec3(0, 1, 0), vec3(0, 1, 0));
// ������ ����������� �������� ��� ������ �� �����
vector<GraphicObject> graphicObjects;

//������� �������
POINT lastCursorPos;


void init() {
	// �������� �������
	shader.load("Scene/Object/GraphicObject/SHADER/Example.vsh", "Scene/Object/GraphicObject/SHADER/Example.fsh");

	//��������� ��������� ������
	camera.setProjectionMatrix(35.0, 800.0 / 600.0, 1.0, 100.0);

	//���������� ������������ ��������
	GraphicObject tempGraphicObj;
	tempGraphicObj.setPosition(vec3(0, 0, 0));
	tempGraphicObj.setColor(vec4(0, 1, 0, 1));
	tempGraphicObj.setAngle(45);
	graphicObjects.push_back(tempGraphicObj);

	tempGraphicObj.setPosition(vec3(0, 1, 0));
	tempGraphicObj.setColor(vec4(1, 1, 0, 1));
	tempGraphicObj.setAngle(0);
	graphicObjects.push_back(tempGraphicObj);

	tempGraphicObj.setPosition(vec3(0, 2, 0));
	tempGraphicObj.setColor(vec4(1, 0, 0, 1));
	tempGraphicObj.setAngle(45);
	graphicObjects.push_back(tempGraphicObj);

	//��������� �������������� �������
	GetCursorPos(&lastCursorPos);
}