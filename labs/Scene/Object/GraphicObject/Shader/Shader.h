#pragma once


#include "../../../../General_Heading.h"

#include <vector>
#include <map>


class Shader
{
public:
	// �������� ������� �� ������� ������
	bool load(std::string veftexShaderFilename, std::string fragmentShaderFilename);

	// ����� ������� � �������� ��������
	void activate();

	// ���������� �������
	static void deactivate();

	// ��������� uniform-����������
	void setUniform(std::string name, int value);
	void setUniform(std::string name, float value);
	void setUniform(std::string name, glm::vec2& value);
	void setUniform(std::string name, glm::vec4& value);
	void setUniform(std::string name, glm::mat4& value);
	void setUniform(std::string, std::vector<glm::mat4>&);

private:
	// �������� ���������� ������� ���������� ���� � �������� ��������� ������ ������� �� ���������� �����
	GLuint createShaderObject(GLenum shaderType, std::string filename);
	// ��������� ������� (location) uniform-����������
	GLuint getUniformLocation(std::string name);
private:
	// id "�������" ��������� ��������� ���������
	// ������������ ����� �������� �� ������������ ��������� ���������, 
	// ���� ��� ��� ������������
	static GLuint currentProgram;
	// ��������� ��������� (������)
	GLuint	program = {};
	// "����������" uniform-����������, ������� ���������� ����� ����������� ������������
	// ����� ������ uniform-���������� � � �������� (location)
	std::map <std::string, GLuint> uniforms;
};
