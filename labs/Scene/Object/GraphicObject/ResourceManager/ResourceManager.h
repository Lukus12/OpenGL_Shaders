#pragma once

#include "../../../../General_Heading.h"
#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
#include "../Material/Material.h"

#include <thread>

using namespace std;

// ����� ��� ������ � ���������� ��������
class ResourceManager
{
public:
	// ������-����� ��� ��������� ���������� ��������� �������.
	// ������ ����� ���������� ������ �� ������, ���������� � ������������ ����������.
	static ResourceManager& instance()
	{
		static ResourceManager ResourceManager;
		return ResourceManager;
	}
	// �������� ������ ���� �� ���������� obj-�����
	// ������������ �������� - ������ ���� � ��������� ��������
	int loadMesh(string filename);
	int loadTexture(string filename);
	int loadMaterial(string filename);
	// ��������� ���� �� ��� �������
	// ���� ������ ���� ��� (���������������� ������) ������������ nullptr
	Mesh* getMesh(int index);
	// ��������� �������� �� � �������
	// ���� ����� �������� ��� (���������������� ������) ������������ nullptr
	Texture* getTexture(int index);
	// ��������� ��������� �� ��� �������
	// ���� ������ ��������� ��� (���������������� ������) ������������ nullptr
	Material* getMaterial(int index);
private:
	// ����������� �� ��������� (�������� ���������)
	// � ���������� ������ ������� �� ������ ������� ������� ������ ��� ������ ������
	ResourceManager() {};
	// ������������ ����������� ��� (������)
	ResourceManager(const ResourceManager& v) = delete;
	// ��������� ������������ ��� (������)
	ResourceManager& operator=(const ResourceManager& v) = delete;
private:
	//������� �����
	void clearMeshes();
	//������� �������
	void clearTextures();
	//������� ����������
	void clearMaterials();
	//����������� �������� �����
	//int asyncLoadMesh(string filename);
private:
	// ������ ��� �������� ���� �����
	vector<Mesh> meshes;
	// ������ ��� �������� ���� �������
	vector<Texture> textures;
	// ������ ��� �������� ���� ����������
	vector<Material> materials;
	// �������� �������� ����� �� �� ������
	map<string, int> meshIndexMap;
	// �������� �������� ������� �� �� ������
	map<string, int> textureIndexMap;
	// �������� �������� ���������� �� �� ������
	map<string, int> materialIndexMap;
};