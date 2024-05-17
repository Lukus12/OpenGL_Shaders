

#include "Data/Data.h"
#include "Display/Display.h"
#include "Display/Simulation.h"

// основная функция
void main(int argc, char** argv)
{
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	// требования к версии OpenGL (версия 3.3 без поддержки обратной совместимости)
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// устанавливаем верхний левый угол окна
	glutInitWindowPosition(300, 100);
	// устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// создание окна
	glutCreateWindow("");
	glutSetWindowTitle("Laba_06 [ ]");
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous);
	// инициализация GLEW 
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
		return;
	}

	// инициализация библиотеки DevIL для загрузки изображений
	ilInit();
	iluInit();
	ilutInit();

	// определение текущей версии OpenGL
	printf("OpenGL Version = %s\n\n", glGetString(GL_VERSION));

	init();

	// устанавливаем функцию, которая будет вызываться при изменении состояния колесика мыши
	glutMouseWheelFunc(mouseWheel);
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию которая вызывается всякий раз, когда процессор простаивает
	glutIdleFunc(simulation);
	// основной цикл обработки сообщений ОС
	glutMainLoop();
	return;
}
