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

		oss << "Laba_07 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}

}


void display()
{
	// ��� �������� ���������� ������ �� RenderManager
	RenderManager& renderManager = RenderManager::instance();

	// �������� ����� ������ �����	
	renderManager.start();
	scene.draw();
	// ��������� ���������� �����
	renderManager.finish();

	sceneInfo = scene.getSceneDescription();
	renderInfo = renderManager.getRenderDescription();

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