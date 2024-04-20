#include "Texture.h"

void Texture::load(std::string filename)
{
	// создаем новое "изображение"
	ILuint imageId = ilGenImage();
	// задаем текущее "изображение"
	ilBindImage(imageId);

	// загружаем изображение
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool result = ilLoadImage(unicodeString);

	if (result) {
		// получение параметров загруженной текстуры
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		//при использовании формата RGBA и типа данных IL_UNSIGNED_BYTE,
		//нужно выделить память для массива размером
		//width * height * depth * 4 байт.
		int dataSize = width * height * 1 * 4;
		void* data = new unsigned char[dataSize];

		//функция ilCopyPixels позволяет скопировать
		//массив пикселей из внутренней памяти библиотеки DevIL в указанный массив,
		//расположенных в оперативной памяти.
		ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);

		// удаляем изображение
		ilDeleteImage(imageId);

		// определяем модель памяти (параметры распаковки)
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//делаем 0 тексурный блок активным
		glActiveTexture(GL_TEXTURE0);
		//Создание текстурного объекта
		glGenTextures(1, &texIndex);
		//Привязка текстурного объекта к текстурному блоку
		glBindTexture(GL_TEXTURE_2D, texIndex);
		//Загрузка изображения из оперативной памяти в текстурный объект
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete[] reinterpret_cast<unsigned char*>(data);
		//Генерация mipmap’ов
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Texture::apply(TextureFilter texFilter)
{
	// Установка параметров текстуры
	switch (texFilter) {
		case TextureFilter::POINT:
			// Установка фильтрации текстуры в точечный режим
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;

		case TextureFilter::BILINEAR:
			// Установка фильтрации текстуры в билинейный режим
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case TextureFilter::TRILINEAR:
			// Установка фильтрации текстуры в трилинейный режим
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case TextureFilter::ANISOTROPIC:
			// Установка фильтрации текстуры в анизотропный режим
			GLfloat maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
			break;
	}
	// Привязываем текстурный объект к текстурному блоку
	glBindTexture(GL_TEXTURE_2D, texIndex);
}

void Texture::disableAll()
{
	glDisable(GL_TEXTURE_2D);
}
