#pragma once

#include "../../../General_Heading.h"

#include "../Mesh/Mesh.h"
#include <thread>

using namespace std;

// КЛАСС ДЛЯ РАБОТЫ С МЕНЕДЖЕРОМ РЕСУРСОВ
class ResourceManager
{
public:
	// Статик-метод для получения экземпляра менеджера ресурса.
	// Всегда будет возвращена ссылка на объект, хранящийся в единственном экземпляре.
	static ResourceManager& instance()
	{
		static ResourceManager ResourceManager;
		return ResourceManager;
	}
	// Загрузка одного меша из указанного obj-файла
	// Возвращаемое значение - индекс меша в менеджере ресурсов
	int loadMesh(string filename);
	// Получение меша по его индексу
	// Если такого меша нет (недействительный индекс) возвращается nullptr
	Mesh* getMesh(int index);
private:
	// конструктор по умолчанию (объявлен приватным)
	// в результате нельзя создать ни одного объекта данного класса вне самого класса
	ResourceManager() {};
	// конструктора копирования нет (удален)
	ResourceManager(const ResourceManager& v) = delete;
	// оператора присваивания нет (удален)
	ResourceManager& operator=(const ResourceManager& v) = delete;
private:
	//очистка мешей
	void clearMeshes();
	//асинхронная загрузка мешей
	//int asyncLoadMesh(string filename);
private:
	// вектор для хранения всех мешей
	vector<Mesh> meshes;
	// Хранение индексов мешей по их именам
	map<std::string, int> meshIndexMap;
};