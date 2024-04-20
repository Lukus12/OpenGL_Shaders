#include "Display.h"

int frameCount = 0;
double interval, fps;
//double allFPS = 0;
double averageFPS = 0;
//������� ���������� fps ����� �� ����� � �������� �� �� ���-�� ������ 1000 ��������(����� ����������)

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

// ������� ��� ������ �������� � ������� ������� ������� (�� -0.5 �� +0.5)
void drawObject()
{
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static bool init = true;
	static GLuint VAO_Index = 0;		// ������ VAO-������
	static GLuint VBO_Index = 0;		// ������ VBO-������
	static int VertexCount = 0;			// ���������� ������

	// ��� ������ ������ �������������� VBO � VAO
	if (init) {
		init = false;
		// �������� � ���������� VBO
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

		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// ���������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		// "�������" ������ VAO, ���� �������� �� ���������
		glBindVertexArray(0);

		// �������� ���������� ������
		VertexCount = 6;
	}

	// ������� �������������
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display()
{
	// �������� ����� �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);

	// ���������� ������
	shader.activate();
	shader.setUniform("offset", offset);
	shader.setUniform("color1", color1);
	shader.setUniform("color2", color2);
	shader.setUniform("color3", color3);

	// ������� ������������� 
	drawObject();

	// ����� ��������� � ������� �������
	glutSwapBuffers();

	// ���������� FPS � ��� ����� � ��������� ����
	winFPS();
}

// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, w, h);
}