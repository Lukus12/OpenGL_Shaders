#include "ResourceManager.h"

/*loadMesh - Данный метод создает один меш, загружает в него указанный файл и помещает меш в вектор.
После этого функция возвращает индекс меша в данном контейнере*/

int ResourceManager::loadMesh(std::string filename)
{
    // Проверяем, был ли ранее загружен такой меш
    // find(). Если элемент не найден, то возвращается итератор,
    // указывающий на позицию за последним элементом в контейнере
    if (meshIndexMap.find(filename) != meshIndexMap.end())
    {
        std::cout << "Mesh '" << filename << "' already loaded. Returning existing index.\n";
        return meshIndexMap[filename]; // если есть, то возвращаем его
    }

    //иначе создаём новый

    Mesh mesh;
    mesh.load(filename);
    meshes.push_back(mesh);
    int index = meshes.size() - 1;
    meshIndexMap[filename] = index; // Сохраняем индекс меша по имени файла

    std::cout << "Mesh '" << filename << "' loaded. Index: " << index << std::endl;
    return index;
}

int ResourceManager::loadTexture(string filename)
{
    // Проверяем, была ли ранее загружена такая текстура
    // find(). Если элемент не найден, то возвращается итератор,
    // указывающий на позицию за последним элементом в контейнере
    if (textureIndexMap.find(filename) != textureIndexMap.end())
    {
        std::cout << "Texture '" << filename << "' already loaded. Returning existing index.\n";
        return textureIndexMap[filename]; // если есть, то возвращаем его
    }

    //иначе создаём новый

    Texture texture;
    texture.load(filename);
    texturs.push_back(texture);
    int index = texturs.size() - 1;
    textureIndexMap[filename] = index; // Сохраняем индекс текстуры по имени файла

    std::cout << "Texture '" << filename << "' loaded. Index: " << index << std::endl;
    return index;
}

Texture* ResourceManager::getTexture(int index)
{
    if (index >= 0 && index < texturs.size()) {
        return &texturs[index];
    }

    return nullptr;
}

Mesh* ResourceManager::getMesh(int index)
{
    if (index >= 0 && index < meshes.size()){
        return &meshes[index];
    }
   
    return nullptr;
}

// Удаление всех мешей
void ResourceManager::clearMeshes()
{
    meshes.clear();
    meshIndexMap.clear();
}

/*int ResourceManager::asyncLoadMesh(string filename)
{
    // Проверяем, был ли ранее загружен такой меш
    if (meshIndexMap.find(filename) != meshIndexMap.end())
    {
        return meshIndexMap[filename]; // если есть, то возвращаем его
    }

    //иначе создаём новый
    Mesh mesh;
    // Запоминаем имя файла и выделяем индекс
    int index = meshes.size();
    meshIndexMap[filename] = index;

    thread([this, mesh, filename]() {
        mesh.load(filename);
    }).detach();
    return meshes.size();
}*/

