#pragma once

#include "../../General_Heading.h"
#include "../Texture/Texture.h"

// ������� ����� ��� ���� ����������
class Material
{
public:
	// "����������" ���������
	virtual void apply(void) = 0;
};
