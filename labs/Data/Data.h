#pragma once

#include "../General_Heading.h"

#include "../Scene/Object/GraphicObject/Shader/Shader.h"
#include "../Scene/Camera/Camera.h"
#include "../Scene/Object/GraphicObject/GraphicObject.h"
#include "../Scene/Object/GraphicObject/ResourceManager/ResourceManager.h"
#include "../Scene/Object/GraphicObject/RenderManager/RenderManager.h"

// используемые пространства имен
using namespace glm;
using namespace std;

extern Shader shader;

extern LARGE_INTEGER previous, frequency;

// ИСПОЛЬЗУЕМАЯ КАМЕРЫ
extern Camera camera;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
extern vector<GraphicObject> graphicObjects;
//Позиция курсора
extern POINT lastCursorPos;

void init();