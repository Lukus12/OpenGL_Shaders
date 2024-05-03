#pragma once

#include "../../../General_Heading.h"

#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"
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
	// ��������� �������� �� � �������
	// ���� ����� �������� ��� (���������������� ������) ������������ nullptr
	Texture* getTexture(int index);
	// ��������� ���� �� ��� �������
	// ���� ������ ���� ��� (���������������� ������) ������������ nullptr
	Mesh* getMesh(int index);
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
	//����������� �������� �����
	//int asyncLoadMesh(string filename);
private:
	// ������ ��� �������� ���� �����
	vector<Mesh> meshes;
	// ������ ��� �������� ���� �������
	vector<Texture> texturs;
	// �������� �������� ����� �� �� ������
	map<string, int> meshIndexMap;
	// �������� �������� ������� �� �� ������
	map<string, int> textureIndexMap;
};