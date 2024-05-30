#pragma once

#include "../General_Heading.h"

#include <vector>

#include "rapidjson/document.h"

#include "Camera/Camera.h"
#include "Object/GraphicObject/GraphicObject.h"
#include "Object/GraphicObject/RenderManager/RenderManager.h"


using namespace std;
using namespace glm;

// КЛАСС ДЛЯ РАБОТЫ СО СЦЕНОЙ
class Scene
{
public:
	// конструктор по умолчанию
	Scene();

	// Инициализация сцены
	// параметр: json-файл с описанием моделей («models.json»)
	void init(std::string filename);
	// загрузка сцены из json-файла
	bool loadFromJson(std::string filename);

	// установка используемой камеры (ссылка на глобальный объект)
	void setCamera(Camera* camera);
	// установка используемого источника света (ссылка на глобальный объект)
	void setLight(Light* light);

	// Вывод всей сцены (посредством обращения к RenderManager)
	void draw();

	// Получение информации о сцене для отладки:
	// [количество объектов переданное на отрисовку]/[общее количество объектов сцены]
	std::string getSceneDescription();

private:
	// создание объекта по его идентификатору в json-файле ("models.json")
	GraphicObject createGraphicObject(std::string model);

	// определение, виден ли объект в зависимости от дистанции до него
	bool lodTest(GraphicObject& graphicObject);
	// определение, попадает ли объект в усечённую пирамиду видимости
	bool frustumCullingTest(GraphicObject& graphicObject, mat4&);

	// json-представление всех моделей (из файла "models.json")
	rapidjson::Document document;

	// указатель на камеру (на глобальную переменную)
	Camera* camera;
	// указатель на источник света (на глобальную переменную)
	Light* light;

	// все графические объекты
	std::vector<GraphicObject> graphicObjects;
	// статистика - сколько объектов передано на отрисовку в текущем кадре
	int renderedObjectCount;
};