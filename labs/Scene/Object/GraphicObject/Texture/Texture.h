#pragma once
#include "../../../../General_Heading.h"

using namespace std;
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ
class Texture
{
public:
	// загрузка текстуры из внешнего файла
	void load(std::string filename);
	// применение текстуры (привязка к текстурному блоку)
	void bind(GLenum texUnit = GL_TEXTURE0);
	// отключение текстурирования для всех текстурных блоков
	static void disableAll();
private:
	// индекс текстурного объекта
	GLuint texIndex;
};
