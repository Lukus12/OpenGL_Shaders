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

		oss << "Laba_04 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}

}


void display()
{
	// �������� ����� �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);

	// ����� ��������� � ���� ����� � ���������� ��������� ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ���������� ������, ������������ ��� ������ �������
	shader.activate();
	// ������������� ������� ��������
	mat4& projectionMatrix = camera.getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);
	// �������� ������� ������
	mat4& viewMatrix = camera.getViewMatrix();
	// ������� ��� �������
	for (auto& graphicObject : graphicObjects) {
		// ������������� ������� ���������� ������
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);
		// ������������� ����
		shader.setUniform("color", graphicObject.getColor());
		// ������� ���
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) mesh->draw();
	}

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
	// ������������� ������� ��������
	camera.setProjectionMatrix(35.0f, (float)w / h, 1.0f, 500.0f);
}