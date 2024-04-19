#include "Shader.h"

using namespace glm;
using namespace std;

// загрузить шейдер
bool Shader::load(string veftexShaderFilename, string fragmentShaderFilename) {
	//создание вершинного шейдера
	GLuint vsh = createShaderObject(GL_VERTEX_SHADER, veftexShaderFilename);
	if (vsh == -1) return false;
	//создание фрагментированного шейдерного объекта
	GLuint fsh = createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename);
	if (fsh == -1) return false;

	//создание шейдреной программы и линковка
	program = glCreateProgram();
	glAttachShader(program, vsh);
	glAttachShader(program, fsh);
	glLinkProgram(program);

	//проверка результата линковки и вывод сообщения об ошибке, если необходимо
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

//создание шейдерного объекта указанного типа и загрузка исходноготекста шейдера из указанного файла
GLuint Shader::createShaderObject(GLenum shaderType, string filename) {
	//буффер для использования
	const int max_buffer_size = 1024 * 10;
	char buffer[max_buffer_size];
	
	ifstream file(filename);
	if (!file.is_open()) {
		return -1;
	}
	//считываем содерживое файла
	file.getline(buffer, max_buffer_size, 0);
	//создание шейдера
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		return -1;
	}

	//указание текста шейдера
	const char* sourch_pointer[] = {buffer};
	glShaderSource(shader, 1, sourch_pointer, 0);

	//компилирование шейдоров
	glCompileShader(shader);

	//проверка результата компилирования и вывод сообщения об ошибке, если необходимо
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		GLuint count;
		glGetShaderInfoLog(shader, max_buffer_size, (GLsizei*)&count, buffer);
		return -1;
	}
	return shader;
}

//активизировать шейдер
void Shader::activate() {
	glUseProgram(program);
}

//отключить шейдер
void Shader::deactivate() {
	glUseProgram(0);
}