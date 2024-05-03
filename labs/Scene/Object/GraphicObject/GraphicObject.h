#pragma once

#include "../../General_Heading.h"

using namespace std;
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С ГРАФИЧЕСКИМ ОБЪЕКТОМ
class GraphicObject
{
public:
	// конструктор по умолчанию
	GraphicObject();
	// установить цвет объекта
	void setColor(vec4 color);
	// установить позицию объекта
	void setPosition(vec3 position);
	// установить угол поворота в градусах относительно оси OY по часовой стрелке
	void setAngle(float degree);
	// установить идентификатор используемого меша
	void setMeshId(int id);
	// установить идентификатор используемой текстуры
	void setTextureId(int id);

	// получить различные параметры
	vec4& getColor();
	mat4& getModelMatrix();
	int getTextureId();
	int getMeshId();
private:
	// идентификатор используемого меша
	int meshId;
	// идентификатор используемой текстуры
	int textureId;
	// цвет объекта
	vec4 color = {};
	// матрица модели (задает позицию и ориентацию)
	mat4 modelMatrix;
	// угол поворота
	float angle;
	//позиция в логических координатах
	vec3 position = {};
	//перерасчет модели матрицы на основании ее угла и положения
	void recalculateModelMatrix();
};
