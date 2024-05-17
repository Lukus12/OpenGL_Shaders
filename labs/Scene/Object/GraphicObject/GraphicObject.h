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
	// установить идентификатор используемого материала
	void setMaterialId(int id);

	// получить параметры и идентификаторы ресурсов
	vec4& getColor();
	mat4& getModelMatrix();
	int getMeshId();
	int getTextureId();
	int getMaterialId();

private:
	// идентификатор используемого меша
	int meshId;
	// идентификатор используемой текстуры
	int textureId;
	// идентификатор используемой текстуры
	int materialId;
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
