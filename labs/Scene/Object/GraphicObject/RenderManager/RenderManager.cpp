#include "RenderManager.h"



void RenderManager::init()
{
	// ����� ���������� ������������� ������� RenderManager ����� ������������� OpenGL
	// �������� ��������, ��������� ���������� � �.�.
	Shader shader;
	shader.load("Data//SHADERS//DiffuseTexture.vsh", "Data//SHADERS/DiffuseTexture.fsh");
	shaders.push_back(shader);

	//������������� ���������
	Light ligth;
	ligth.setDirection(vec3(0, 5, 5));
	ligth.setDiffuse(vec4(1, 1, 1, 1));
	ligth.setAmbient(vec4(0.5, 0.5, 0.5, 1));
	ligth.setSpecular(vec4(0.5, 0.5, 0.5, 1));
	lights.push_back(ligth);

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
	Shader shader = shaders[0];
	shader.activate();

	// ������������� ������� ��������
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);

	// �������� ������� ������
	mat4& viewMatrix = camera->getViewMatrix();

	// ����� ���������
	Light* lightActiv = &(lights[0]);
	vec4 lightVector = viewMatrix * lightActiv->getDirection();

	shader.setUniform("lAmbient", lightActiv->getAmbient());
	shader.setUniform("lDiffuse", lightActiv->getDiffuse());
	shader.setUniform("lSpecular", lightActiv->getSpecular());
	shader.setUniform("lPosition", lightVector);

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

		//������������� �������� 
		int materialId = graphicObject.getMaterialId();
		Material* material = ResourceManager::instance().getMaterial(materialId);
		if (material != nullptr) {
			shader.setUniform("mAmbient", material->getAmbient());
			shader.setUniform("mDiffuse", material->getDiffuse());
			shader.setUniform("mSpecular", material->getSpecular());
			shader.setUniform("mShininess", material->getShininess());
		}

		// ������� ���
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) mesh->draw();
	}
}
