#pragma once

#include "../Scene/Object/GraphicObject/RenderManager/RenderManager.h"

#include "../Scene/Scene.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

extern LARGE_INTEGER previous, frequency;

// ������������ ������
extern Camera camera;
// ������ ����������� �������� ��� ������ �� �����
extern vector<GraphicObject> graphicObjects;
//������� �������
extern POINT lastCursorPos;

extern Light light;
extern Scene scene;

extern string renderInfo;
extern string sceneInfo;

void init();