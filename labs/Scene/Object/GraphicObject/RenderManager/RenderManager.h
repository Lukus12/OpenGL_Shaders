#pragma once
#include "../../../General_Heading.h"

#include <algorithm>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "../../Data/Data.h"

// ����� ��� �������������� � OPENGL
// ���� ����� �������������� ����� ������������ ��������� ������� ������
class RenderManager
{
public:
	// ������-����� ��� ��������� ���������� ��������� �������.
	static RenderManager& instance()
	{
		static RenderManager renderManager;
		return renderManager;
	}
	// ������������� ������� RenderManager, ����������� ����� ������������� OpenGL:
	// �������� ��������, ��������� ���������� ���������� � ������ �������������
	void init();
	// ������ ������ ���������� ����� (����������, ������� ������� ����������� ��������)
	void start();
	// ��������� ������������ ������
	void setCamera(Camera* camera);
	// ���������� � ������� ���������� ���������� ������� ��� ������
	void addToRenderQueue(GraphicObject& graphicObject);
	// ���������� ������ ����� (�������� ������)
	void finish();
private:
	// ����������� �� ��������� (���������)
	RenderManager() {};
	// ������������ ����������� ���
	RenderManager(const RenderManager& root) = delete;
	// ��������� ������������ ���
	RenderManager& operator=(const RenderManager&) = delete;
private:
	// ������������ ������� 
	std::vector<Shader> shaders;
	// ��������� �� ������
	Camera* camera = {};
	// ������ ����������� ��������, ������� ���������� ������� � ������ �����
	std::vector<GraphicObject> graphicObjects;
};