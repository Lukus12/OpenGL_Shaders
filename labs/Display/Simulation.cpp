
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;

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
	// вычисление нового смещения и изменение прочих параметров
	offset = offset + (simulationTime / 1000 * speed);
	// ограничения
	if (offset.x + 0.5 >= 1) speed.x = -speed.x;
	if (offset.x - 0.5 <= -1) speed.x = -speed.x;
	if (offset.y + 0.5 >= 1) speed.y = -speed.y;
	if (offset.y - 0.5 <= -1) speed.y = -speed.y;

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};