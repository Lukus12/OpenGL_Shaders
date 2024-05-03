#pragma once
#include "../../General_Heading.h"

using namespace std;
using namespace glm;

// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);
	// ���������� �������� (�������� � ����������� �����)
	void bind(GLenum texUnit = GL_TEXTURE0);
private:
	// ������ ����������� �������
	GLuint texIndex;
};
