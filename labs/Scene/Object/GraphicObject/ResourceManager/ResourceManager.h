#pragma once

#include "../../../General_Heading.h"

#include "../Mesh/Mesh.h"
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
	// �������� �������� ����� �� �� ������
	map<std::string, int> meshIndexMap;
};