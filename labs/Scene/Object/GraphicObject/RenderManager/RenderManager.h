#pragma once
#include "../../../General_Heading.h"

#include <algorithm>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "../Shader/Shader.h"
#include "../../Scene/Camera/Camera.h"
#include "../GraphicObject.h"
#include "../ResourceManager/ResourceManager.h"
#include "..//Material/Material.h"
#include "../../Scene/Lighting/Light.h"

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
	// установка используемой камеры
	void setCamera(Camera* camera);
	// добавление в очередь рендеринга очередного объекта для вывода
	void addToRenderQueue(GraphicObject& graphicObject);
	// завершение вывода кадра (основная работа)
	void finish();
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
	// список графических объектов, которые необходимо вывести в данном кадре
	std::vector<GraphicObject> graphicObjects;
};