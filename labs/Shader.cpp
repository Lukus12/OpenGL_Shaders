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

//Uniform параметры

void Shader::setUniform(std::string name, int value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// Обработка ошибки: униформ с таким именем не найден
		return;
	}
	glUniform1i(uniformLocation, value);
}

void Shader::setUniform(std::string name, float value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// Обработка ошибки: униформ с таким именем не найден
		return;
	}
	glUniform1f(uniformLocation, value);
}

void Shader::setUniform(std::string name, glm::vec2& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// Обработка ошибки: униформ с таким именем не найден
		return;
	}
	glUniform2fv(uniformLocation, 1, &value[0]);
}

void Shader::setUniform(std::string name, glm::vec4& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// Обработка ошибки: униформ с таким именем не найден
		return;
	}
	glUniform4fv(uniformLocation, 1, &value[0]);
}

void Shader::setUniform(std::string name, glm::mat4& value)
{
	GLuint uniformLocation = getUniformLocation(name);
	if (uniformLocation == -1)
	{
		// Обработка ошибки: униформ с таким именем не найден
		return;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

// получение индекса (location) uniform-переменной
GLuint Shader::getUniformLocation(std::string name)
{
	// Проверяем, есть ли индекс в map-е
	if (uniforms.find(name) != uniforms.end()){
		return uniforms[name]; // если есть, то возвращаем
	}

	// Иначе ищем индекс переменной и добавляем
	GLuint location = glGetUniformLocation(program, name.c_str());
	if (location != -1){
		// Сохраняем индекс в map
		uniforms[name] = location;
	}
	else {
		cout << "Error handling : no uniform with the name " << name << " was found" << endl;
	}
	return location;
}

