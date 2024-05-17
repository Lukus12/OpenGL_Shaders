#pragma once

#include "../Scene/Object/GraphicObject/RenderManager/RenderManager.h"

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

void init();