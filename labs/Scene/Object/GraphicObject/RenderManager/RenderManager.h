#pragma once

#include "../../../../General_Heading.h"

#include "../../../../Scene/FBO/Variables.h"
#include "../../../Lighting/Light.h"
#include "../Shader/Shader.h"
#include "../../../Camera/Camera.h"
#include "../GraphicObject.h"
#include "../ResourceManager/ResourceManager.h"
#include "..//Material/Material.h"
#include "../../../Camera/Camera.h"

// КЛАСС ДЛЯ ВЗАИМОДЕЙСТВИЯ С OPENGL
// ВЕСЬ ВЫВОД ОСУЩЕСТВЛЯЕТСЯ ЧЕРЕЗ ЕДИНСТВЕННЫЙ ЭКЗЕМПЛЯР ДАННОГО КЛАССА
class RenderManager
{
public:
	// Статик-метод для получения экземпляра менеджера ресурса.
	static RenderManager& instance()
	{
		static RenderManager renderManager;
		return renderManager;
	}
	// инициализация объекта RenderManager, выполняется после инициализации OpenGL:
	// загрузка шейдеров, установка неизменных параметров и прочая инициализация
	void init();
	// Начало вывода очередного кадра (подготовка, очистка вектора графических объектов)
	void start();
	void draw(vector<mat4>&, vector<Shader>&, int);
	// установка используемой камеры
	void setCamera(Camera* camera);
	void setLight(Light* light);

	// выводим все объекты
	void drawAllObjects();

	// добавление в очередь рендеринга очередного объекта для вывода
	void addToRenderQueue(GraphicObject& graphicObject);
	// завершение вывода кадра (основная работа)
	void finish();
	string getRenderDescription();
private:
	// конструктор по умолчанию (приватный)
	RenderManager() {};
	// конструктора копирования нет
	RenderManager(const RenderManager& root) = delete;
	// оператора присваивания нет
	RenderManager& operator=(const RenderManager&) = delete;
private:
	// используемые шейдеры 
	std::vector<Shader> shaders = {};
	// используемые источники света 
	std::vector<Light> lights = {};
	// указатель на камеру
	Camera* camera = {};
	Light* light = {};
	// список графических объектов, которые необходимо вывести в данном кадре
	std::vector<GraphicObject> graphicObjects;

	void drawQuad();

	int materialChanged;
	int textureChanged;
	int drawCallCount;
};