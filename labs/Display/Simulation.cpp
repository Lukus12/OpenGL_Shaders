
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;

unsigned int modeChangeClocks = clock();

void moveCamera(float simulationTime);

double getSimulationTime() {
	float time;
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	time = (float)(end.QuadPart - previous.QuadPart) / frequency.QuadPart;
	return time;
};

void simulation()
{
	// определение времени симуляции
	float simulationTime = getSimulationTime();

	moveCamera(simulationTime);
	
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};

void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 500 * simulationTime;
	float SpeedVertical = 15000 * simulationTime;
	float SpeedZoom = 200 * simulationTime;

	if (GetAsyncKeyState(VK_UP)) camera.moveOXZ(0, SpeedVertical);
	if (GetAsyncKeyState(VK_DOWN)) camera.moveOXZ(0, -SpeedVertical);
	if (GetAsyncKeyState(VK_LEFT)) camera.moveOXZ(-SpeedHorizontal, 0);
	if (GetAsyncKeyState(VK_RIGHT)) camera.moveOXZ(SpeedHorizontal, 0);

	if (GetAsyncKeyState(0x31)) {
		if (clock() - modeChangeClocks > 200) {
			postProcessingMode++;
			if (postProcessingMode > 3) postProcessingMode = 0;
			modeChangeClocks = clock();
		}
	}

	//поворот камеры на правую кнопку мыши
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	if (GetAsyncKeyState(VK_RBUTTON)) {
		camera.rotate((cursorPos.x - lastCursorPos.x) / 10.0, (cursorPos.y - lastCursorPos.y) / 10.0);
	}
	lastCursorPos = cursorPos;

};
// функция обработки вращения колесика мышки
void mouseWheel(int wheel, int direction, int x, int y)
{
	// определяем, на сколько необходимо приблизить/удалить камеру
	float delta = 100 * getSimulationTime();

	if (direction > 0) camera.zoom(delta);
	else camera.zoom(-delta);
}