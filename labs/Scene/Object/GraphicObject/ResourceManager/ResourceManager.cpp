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

