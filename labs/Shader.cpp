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

//Uniform ���������

void Shader::setUniform(std::string name, int value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// ��������� ������: ������� � ����� ������ �� ������
		return;
	}
	glUniform1i(uniformLocation, value);
}

void Shader::setUniform(std::string name, float value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// ��������� ������: ������� � ����� ������ �� ������
		return;
	}
	glUniform1f(uniformLocation, value);
}

void Shader::setUniform(std::string name, glm::vec2& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// ��������� ������: ������� � ����� ������ �� ������
		return;
	}
	glUniform2fv(uniformLocation, 1, &value[0]);
}

void Shader::setUniform(std::string name, glm::vec4& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// ��������� ������: ������� � ����� ������ �� ������
		return;
	}
	glUniform4fv(uniformLocation, 1, &value[0]);
}

void Shader::setUniform(std::string name, glm::mat4& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// ��������� ������: ������� � ����� ������ �� ������
		return;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

// ��������� ������� (location) uniform-����������
GLuint Shader::getUniformLocation(std::string name)
{
	// ���������, ���� �� ������ � map-�
	if (uniforms.find(name) != uniforms.end()){
		return uniforms[name]; // ���� ����, �� ����������
	}

	// ����� ���� ������ ���������� � ���������
	GLuint location = glGetUniformLocation(program, name.c_str());
	if (location != -1){
		// ��������� ������ � map
		uniforms[name] = location;
	}
	else {
		cout << "Error handling : no uniform with the name " << name << " was found" << endl;
	}
	return location;
}

