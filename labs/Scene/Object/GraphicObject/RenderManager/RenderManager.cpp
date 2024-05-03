#include "RenderManager.h"

void RenderManager::init()
{
	// ����� ���������� ������������� ������� RenderManager ����� ������������� OpenGL
	// �������� ��������, ��������� ���������� � �.�.
	
	// �������� �������
	shader.load("Data//SHADER//Example.vsh", "Data//SHADER/Example.fsh");
}

void RenderManager::start()
{
	// ������� ������� ����������� ��������
	graphicObjects.clear();

	// �������� ����� �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� ������� (�� ������ ������)
	glEnable(GL_DEPTH_TEST);

	// ����� ��������� � ���� ����� � ���������� ��������� ������
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

}

void RenderManager::setCamera(Camera* camera)
{
	this->camera = camera;
}

void RenderManager::addToRenderQueue(GraphicObject& graphicObject)
{
	this->graphicObjects.push_back(graphicObject);
}

void RenderManager::finish()
{
	// ���������� ������, ������������ ��� ������ �������
	shader.activate();
	// ������������� ������� ��������
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);
	// �������� ������� ������
	mat4& viewMatrix = camera->getViewMatrix();
	// ������� ��� �������
	for (auto& graphicObject : graphicObjects) {
		// ������������� ������� ���������� ������
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);

		// ������������� �������� (����������� � ����������� �����)
		int textureId = graphicObject.getTextureId();
		Texture* texture = ResourceManager::instance().getTexture(textureId);
		if (texture != nullptr) texture->bind(GL_TEXTURE0);

		// uniform-���������� texture_0 �������� � ������� ���������� ������ 
		shader.setUniform("texture_0", 0);

		// ������� ���
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) mesh->draw();
	}
}
