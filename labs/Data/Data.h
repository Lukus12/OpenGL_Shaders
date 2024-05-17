#pragma once

#include "../Scene/Object/GraphicObject/RenderManager/RenderManager.h"

// используемые пространства имен
using namespace glm;
using namespace std;

extern LARGE_INTEGER previous, frequency;

// ИСПОЛЬЗУЕМАЯ КАМЕРЫ
extern Camera camera;
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
extern vector<GraphicObject> graphicObjects;
//Позиция курсора
extern POINT lastCursorPos;

void init();