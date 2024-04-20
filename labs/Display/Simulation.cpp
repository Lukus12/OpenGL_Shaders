
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;

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
	// ����������� ������� ���������
	float simulationTime = getSimulationTime();

	moveCamera(simulationTime);
	
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};

void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 100 * simulationTime;
	float SpeedVertical = 400 * simulationTime;
	float SpeedZoom = 200 * simulationTime;

	if (GetAsyncKeyState(VK_UP)) camera.moveOXZ(0, SpeedVertical);
	if (GetAsyncKeyState(VK_DOWN)) camera.moveOXZ(0, -SpeedVertical);
	if (GetAsyncKeyState(VK_LEFT)) camera.moveOXZ(-SpeedHorizontal, 0);
	if (GetAsyncKeyState(VK_RIGHT)) camera.moveOXZ(SpeedHorizontal, 0);

	//������� ������ �� ������ ������ ����
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	if (GetAsyncKeyState(VK_RBUTTON)) {
		camera.rotate((cursorPos.x - lastCursorPos.x) / 10.0, (cursorPos.y - lastCursorPos.y) / 10.0);
	}
	lastCursorPos = cursorPos;

};
// ������� ��������� �������� �������� �����
void mouseWheel(int wheel, int direction, int x, int y)
{
	// ����������, �� ������� ���������� ����������/������� ������
	float delta = 100 * getSimulationTime();

	if (direction > 0) camera.zoom(delta);
	else camera.zoom(-delta);
}