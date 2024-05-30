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

		oss << "Laba_07 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}

}


void display()
{
	// для удобства определяем ссылку на RenderManager
	RenderManager& renderManager = RenderManager::instance();

	// начинаем вывод нового кадра	
	renderManager.start();
	scene.draw();
	// завершаем построение кадра
	renderManager.finish();

	sceneInfo = scene.getSceneDescription();
	renderInfo = renderManager.getRenderDescription();

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
	// устанавливаем матрицу проекции
	camera.setProjectionMatrix(35.0f, (float)w / h, 1.0f, 500.0f);
}