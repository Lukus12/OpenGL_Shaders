#include "Data.h"

LARGE_INTEGER previous, frequency;

// ИСПОЛЬЗУЕМАЯ КАМЕРЫ
Camera camera(vec3(-10.0, 14.0, 30.0), vec3(0, 0, 5), vec3(0, 1, 0));
// СПИСОК ГРАФИЧЕСКИХ ОБЪЕКТОВ ДЛЯ ВЫВОДА НА ЭКРАН
vector<GraphicObject> graphicObjects;

//Позиция курсора
POINT lastCursorPos;

Light light;
Scene scene;

string renderInfo;
string sceneInfo;


void init() {


	RenderManager& renderManager = RenderManager::instance();
	renderManager.init();
	renderManager.setCamera(&camera);
	renderManager.setLight(&light);

	scene.setCamera(&camera);
	scene.init("Data//models.json");
	scene.loadFromJson("Data//SCENES//big_scene.json");

	//начальное положение камеры
	//camera.setProjectionMatrix(35.0, 800.0 / 600.0, 1.0, 100.0);
	//начальное местоположение курсора
	GetCursorPos(&lastCursorPos);
}