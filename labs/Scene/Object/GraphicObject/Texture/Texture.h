#pragma once
#include "../../General_Heading.h"


// ������������ ��� ����������� ������ ����������
enum class TextureFilter {
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};
// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);

	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
};