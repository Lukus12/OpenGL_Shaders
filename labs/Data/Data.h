#pragma once

#include "../General_Heading.h"

#include "../Shader.h"
#include "../Scene/Camera/Camera.h"
#include "../Scene/Object/GraphicObject/GraphicObject.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

extern Shader shader;

extern LARGE_INTEGER previous, frequency;

// ������������ ������
extern Camera camera;
// ������ ����������� �������� ��� ������ �� �����
extern vector<GraphicObject> graphicObjects;
//������� �������
extern POINT lastCursorPos;

void init();