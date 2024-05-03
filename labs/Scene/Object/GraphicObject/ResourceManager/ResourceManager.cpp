#include "ResourceManager.h"

/*loadMesh - ������ ����� ������� ���� ���, ��������� � ���� ��������� ���� � �������� ��� � ������.
����� ����� ������� ���������� ������ ���� � ������ ����������*/

int ResourceManager::loadMesh(std::string filename)
{
    // ���������, ��� �� ����� �������� ����� ���
    // find(). ���� ������� �� ������, �� ������������ ��������,
    // ����������� �� ������� �� ��������� ��������� � ����������
    if (meshIndexMap.find(filename) != meshIndexMap.end())
    {
        std::cout << "Mesh '" << filename << "' already loaded. Returning existing index.\n";
        return meshIndexMap[filename]; // ���� ����, �� ���������� ���
    }

    //����� ������ �����

    Mesh mesh;
    mesh.load(filename);
    meshes.push_back(mesh);
    int index = meshes.size() - 1;
    meshIndexMap[filename] = index; // ��������� ������ ���� �� ����� �����

    std::cout << "Mesh '" << filename << "' loaded. Index: " << index << std::endl;
    return index;
}

int ResourceManager::loadTexture(string filename)
{
    // ���������, ���� �� ����� ��������� ����� ��������
    // find(). ���� ������� �� ������, �� ������������ ��������,
    // ����������� �� ������� �� ��������� ��������� � ����������
    if (textureIndexMap.find(filename) != textureIndexMap.end())
    {
        std::cout << "Texture '" << filename << "' already loaded. Returning existing index.\n";
        return textureIndexMap[filename]; // ���� ����, �� ���������� ���
    }

    //����� ������ �����

    Texture texture;
    texture.load(filename);
    texturs.push_back(texture);
    int index = texturs.size() - 1;
    textureIndexMap[filename] = index; // ��������� ������ �������� �� ����� �����

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

// �������� ���� �����
void ResourceManager::clearMeshes()
{
    meshes.clear();
    meshIndexMap.clear();
}

/*int ResourceManager::asyncLoadMesh(string filename)
{
    // ���������, ��� �� ����� �������� ����� ���
    if (meshIndexMap.find(filename) != meshIndexMap.end())
    {
        return meshIndexMap[filename]; // ���� ����, �� ���������� ���
    }

    //����� ������ �����
    Mesh mesh;
    // ���������� ��� ����� � �������� ������
    int index = meshes.size();
    meshIndexMap[filename] = index;

    thread([this, mesh, filename]() {
        mesh.load(filename);
    }).detach();
    return meshes.size();
}*/

