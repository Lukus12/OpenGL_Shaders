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
	void draw(vector<mat4>&, vector<Shader>&, int);
	// ��������� ������������ ������
	void setCamera(Camera* camera);
	void setLight(Light* light);

	// ������� ��� �������
	void drawAllObjects();

	// ���������� � ������� ���������� ���������� ������� ��� ������
	void addToRenderQueue(GraphicObject& graphicObject);
	// ���������� ������ ����� (�������� ������)
	void finish();
	string getRenderDescription();
private:
	// ����������� �� ��������� (���������)
	RenderManager() {};
	// ������������ ����������� ���
	RenderManager(const RenderManager& root) = delete;
	// ��������� ������������ ���
	RenderManager& operator=(const RenderManager&) = delete;
private:
	// ������������ ������� 
	std::vector<Shader> shaders = {};
	// ������������ ��������� ����� 
	std::vector<Light> lights = {};
	// ��������� �� ������
	Camera* camera = {};
	Light* light = {};
	// ������ ����������� ��������, ������� ���������� ������� � ������ �����
	std::vector<GraphicObject> graphicObjects;

	void drawQuad();

	int materialChanged;
	int textureChanged;
	int drawCallCount;
};