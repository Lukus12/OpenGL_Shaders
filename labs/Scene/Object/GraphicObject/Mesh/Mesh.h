#pragma once

#include "../../General_Heading.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;
using namespace glm;

struct Vertex
{
	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока 
	GLfloat texCoord[2];
};

class Mesh
{
public:
	// загрузка меша из файла с указанным именем
	void load(std::string filename);
	// вывод меша (передача всех вершин в OpenGL)
	void draw();
private:
	// количество индексов 
	int indexCount;
	// индексы (идентификаторы) буферов OpenGL
	GLuint bufferIds[2];
};