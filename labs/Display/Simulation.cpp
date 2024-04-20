
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
	// ����������� ������� ���������
	float simulationTime = getSimulationTime();
	// ���������� ������ �������� � ��������� ������ ����������
	offset = offset + (simulationTime / 1000 * speed);
	// �����������
	if (offset.x + 0.5 >= 1) speed.x = -speed.x;
	if (offset.x - 0.5 <= -1) speed.x = -speed.x;
	if (offset.y + 0.5 >= 1) speed.y = -speed.y;
	if (offset.y - 0.5 <= -1) speed.y = -speed.y;

	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};