#include "Display.h"

int frameCount = 0;
double interval, fps;
//double allFPS = 0;
double averageFPS = 0;
//считать результаты fps через их сумму и поделить на их кол-во спустя 1000 миллисек(сумма интервалов)

double allInterval = 0;

void winFPS() {
	std::ostringstream oss;
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	interval = static_cast<double>(current.QuadPart - previous.QuadPart) / frequency.QuadPart;
	allInterval += interval;

	previous = current;

	frameCount++;


	if (allInterval > 1) {

		averageFPS = frameCount / allInterval;
		allInterval -= 1;

		frameCount = 0;

		oss << "Laba_02 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}

}

// функция для вывода квадрата с ребрами равными единице (от -0.5 до +0.5)
void drawObject()
{
	// переменные для вывода объекта (прямоугольника из двух треугольников)
	static bool init = true;
	static GLuint VAO_Index = 0;		// индекс VAO-буфера
	static GLuint VBO_Index = 0;		// индекс VBO-буфера
	static int VertexCount = 0;			// количество вершин

	// при первом вызове инициализируем VBO и VAO
	if (init) {
		init = false;
		// создание и заполнение VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat	Verteces[] = {
			-0.5,	+0.5,
			-0.5,	-0.5,
			+0.5,	+0.5,
			+0.5,	+0.5,
			-0.5,	-0.5,
			+0.5,	-0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// создание VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// заполнение VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		// "отвязка" буфера VAO, чтоб случайно не испортить
		glBindVertexArray(0);

		// указание количество вершин
		VertexCount = 6;
	}

	// выводим прямоугольник
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display()
{
	// отчищаем буфер кадра
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);

	// активируем шейдер
	shader.activate();
	shader.setUniform("offset", offset);
	shader.setUniform("color1", color1);
	shader.setUniform("color2", color2);
	shader.setUniform("color3", color3);

	// выводим прямоугольник 
	drawObject();

	// смена переднего и заднего буферов
	glutSwapBuffers();

	// вычисление FPS и его вывод в заголовок окна
	winFPS();
}

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, w, h);
}