#pragma once
#include "../../General_Heading.h"


// ПЕРЕЧИСЛЕНИЕ ДЛЯ ОПРЕДЕЛЕНИЯ РЕЖИМА ФИЛЬТРАЦИИ
enum class TextureFilter {
	POINT, // ТОЧЕЧНАЯ
	BILINEAR, // БИЛИНЕЙНАЯ
	TRILINEAR, // ТРИЛИНЕЙНАЯ
	ANISOTROPIC // АНИЗТОРОПНАЯ
};
// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ
class Texture
{
public:
	// загрузка текстуры из внешнего файла
	void load(std::string filename);

	// применение текстуры (привзяка к текстурному блоку и установка параметров)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// отключение текстурирования для всех текстурных блоков
	static void disableAll();
private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
};