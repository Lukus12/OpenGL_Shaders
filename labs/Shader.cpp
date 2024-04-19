#include "Shader.h"

using namespace glm;
using namespace std;

// ��������� ������
bool Shader::load(string veftexShaderFilename, string fragmentShaderFilename) {
	//�������� ���������� �������
	GLuint vsh = createShaderObject(GL_VERTEX_SHADER, veftexShaderFilename);
	if (vsh == -1) return false;
	//�������� ������������������ ���������� �������
	GLuint fsh = createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename);
	if (fsh == -1) return false;

	//�������� ��������� ��������� � ��������
	program = glCreateProgram();
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);

	//�������� ���������� �������� � ����� ��������� �� ������, ���� ����������
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		GLuint count;
		char errorLog[1024];
		glGetProgramInfoLog(program, 1024, (GLsizei*)&count, errorLog);
		return false;
	}
	return true;
}

//�������� ���������� ������� ���������� ���� � �������� ��������������� ������� �� ���������� �����
GLuint Shader::createShaderObject(GLenum shaderType, string filename) {
	//������ ��� �������������
	const int max_buffer_size = 1024 * 10;
	char buffer[max_buffer_size];
	
	ifstream file(filename);
	if (!file.is_open()) {
		return -1;
	}
	//��������� ���������� �����
	file.getline(buffer, max_buffer_size, 0);
	//�������� �������
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		return -1;
	}

	//�������� ������ �������
	const char* sourch_pointer[] = {buffer};
	glShaderSource(shader, 1, sourch_pointer, 0);

	//�������������� ��������
	glCompileShader(shader);

	//�������� ���������� �������������� � ����� ��������� �� ������, ���� ����������
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		GLuint count;
		glGetShaderInfoLog(shader, max_buffer_size, (GLsizei*)&count, buffer);
		return -1;
	}
	return shader;
}

//�������������� ������
void Shader::activate() {
	glUseProgram(program);
}

//��������� ������
void Shader::deactivate() {
	glUseProgram(0);
}