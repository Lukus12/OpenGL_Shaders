#pragma once

#include "../../../../General_Heading.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;
using namespace glm;

struct Vertex
{
	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� ����� 
	GLfloat texCoord[2];
};

class Mesh
{
public:
	// �����������
	Mesh();
	// �������� ���� �� ����� � ��������� ������
	void load(std::string filename);
	// ����� ���� (�������� ���� ������ � OpenGL)
	void drawOne();
	void drawMany(int count);
private:
	// ���������� �������� (������ � ����)
	int indexCount;
	// ������� (��������������) ������� OpenGL
	GLuint bufferIds[2];
	// ���������� ���������� ��� �������� �������������� VAO-������� (������ VAO-�������)
	GLuint VAO;
	// ������ VBO-������ ������
	GLuint vertexVAOBuffer;
	// ������ VBO-������ ��������
	GLuint indexVAOBuffer;
};