#pragma once

#include "../../General_Heading.h"
#include "../Texture/Texture.h"

// БАЗОВЫЙ КЛАСС ДЛЯ ВСЕХ МАТЕРИАЛОВ
class Material
{
public:
	// "применение" материала
	virtual void apply(void) = 0;
};
