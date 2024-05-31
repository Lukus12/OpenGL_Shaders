#include "RenderManager.h"

void RenderManager::draw(vector<mat4>& matrices, vector<Shader>& sh, int meshId)
{
	if (matrices.size() > 0) {
		sh[0].setUniform("modelViewMatrix", matrices);
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) {
			mesh->drawMany(matrices.size());
		}
		matrices.clear();
		drawCallCount++;
	}
}

void RenderManager::drawAllObjects()
{
	materialChanged = 0;
	textureChanged = 0;
	drawCallCount = 0;

	// �������� ������� ������
	mat4& viewMatrix = camera->getViewMatrix();
	int prevMaterialId = -1;
	int prevTextureId = -1;
	int prevMeshId = -1;
	vector<mat4>modelMatrices;

	for (auto& graphicObject : graphicObjects) {
		int materialId = graphicObject.getMaterialId();
		if (prevMaterialId != materialId) {
			draw(modelMatrices, shaders, prevMeshId);
			Material* mater = ResourceManager::instance().getMaterial(materialId);

			if (mater != nullptr) {
				shaders[0].setUniform("mAmbient", mater->getAmbient());
				shaders[0].setUniform("mDiffuse", mater->getDiffuse());
				shaders[0].setUniform("mSpecular", mater->getSpecular());
				shaders[0].setUniform("mShininess", mater->getShininess());
			}

			prevMaterialId = materialId;
			materialChanged++;
		}

		int textureId = graphicObject.getTextureId();
		if (prevTextureId != textureId) {
			draw(modelMatrices, shaders, prevMeshId);
			Texture* texture = ResourceManager::instance().getTexture(textureId);

			if (texture != nullptr) {
				texture->bind(GL_TEXTURE0);
			}

			shaders[0].setUniform("texture_0", 0);
			prevTextureId = textureId;
			textureChanged++;
		}

		//������� ���
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		int meshId = graphicObject.getMeshId();

		if (prevMeshId != meshId) {
			draw(modelMatrices, shaders, prevMeshId);
			prevMeshId = meshId;
		}

		// ������������� ������� ���������� ������
		modelMatrices.push_back(modelViewMatrix);
		if (modelMatrices.size() >= 20) {
			draw(modelMatrices, shaders, prevMeshId);
		}
	}
	Texture::disableAll();
}

// ������������� ������� RenderManager, ����������� ����� ������������� OpenGL:
// �������� ��������, ��������� ���������� ���������� � ������ �������������
void RenderManager::init()
{
	// ������������ ������ (���� ������ ����)
	Shader shader;
	// �������� �������
	shader.load("Data//SHADERS//DiffuseTextureInstanced.vsh", "Data//SHADERS//DiffuseTextureInstanced.fsh");
	shaders.push_back(shader);

	shader.load("Data//SHADERS//SimplePostProcessing.vsh", "Data//SHADERS//SimplePostProcessing.fsh");
	shaders.push_back(shader);

	shader.load("Data//SHADERS//GreyPostProcessing.vsh", "Data//SHADERS//GreyPostProcessing.fsh");
	shaders.push_back(shader);

	shader.load("Data//SHADERS//SepiaPostProcessing.vsh", "Data//SHADERS//SepiaPostProcessing.fsh");
	shaders.push_back(shader);

	shader.load("Data//SHADERS//MyFilter.vsh", "Data//SHADERS//MyFilter.fsh");
	shaders.push_back(shader);

	fbos[0].init(windowWidth, windowHeight, true);
	fbos[1].init(windowWidth, windowHeight, false);
}

void RenderManager::start()
{
	// ��������� �������
	shaders[0].activate();

	// ������������� ������� ��������
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shaders[0].setUniform("projectionMatrix", projectionMatrix);

	//������������� ��������� �����
	shaders[0].setUniform("lAmbient", light->getAmbient());
	shaders[0].setUniform("lDiffuse", light->getDiffuse());
	shaders[0].setUniform("lSpecular", light->getSpecular());
	shaders[0].setUniform("lPosition", light->getDirection());

	//������� ������� ��������
	graphicObjects.clear();
}

// ��������� ������������ ������
void RenderManager::setCamera(Camera* camera)
{
	this->camera = camera;
}

void RenderManager::setLight(Light* light)
{
	this->light = light;
}

// ���������� � ������� ���������� ���������� ������� ��� ������
void RenderManager::addToRenderQueue(GraphicObject& graphicObject)
{
	graphicObjects.push_back(graphicObject);
}

// ���������� ������ ����� (�������� ������)
void RenderManager::finish()
{
	// �������� ����� FBO � ����������������
	fbos[0].bind();

	// �������� ����� �����
	glClearColor(0.880, 0.890, 0.910, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������������� ��������� �������������� ��������� ����������
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ������� ��� �������
	drawAllObjects();

	// �������� ����� � ���������������� � ������� �����
	fbos[0].resolveToFbo(fbos[1]);

	// ������������� � ������������ ������ �����
	FBO::unbind();
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.880, 0.890, 0.910, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// ������� ��������� � ���������� �� �� ���������
	fbos[1].bindColorTexture(GL_TEXTURE0);
	shaders[postProcessingMode + 1].activate();
	shaders[postProcessingMode + 1].setUniform("texture_0", 0);

	drawQuad();
}

string RenderManager::getRenderDescription()
{
	return "[Material changed: " + to_string(materialChanged) +
		"][Texture changed: " + to_string(textureChanged) +
		"][Draw calls: " + to_string(drawCallCount) + "]";
}

void RenderManager::drawQuad() {
	// ���������� ��� ������ ������� (�������������� �� ���� �������������)
	static bool init = true;
	static GLuint VAO_Index = 0;		// ������ VAO-������
	static GLuint VBO_Index = 0;		// ������ VBO-������
	static int VertexCount = 0;			// ���������� ������

	// ��� ������ ������ �������������� VBO � VAO
	if (init) {
		init = false;
		// �������� � ���������� VBO
		glGenBuffers(1, &VBO_Index);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		GLfloat	Verteces[] = {

			-0.5, +0.5,
			-0.5, -0.5,
			+0.5, +0.5,
			+0.5, +0.5,
			-0.5, -0.5,
			+0.5, -0.5
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

		// �������� VAO
		glGenVertexArrays(1, &VAO_Index);
		glBindVertexArray(VAO_Index);
		// ���������� VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		// "�������" ������ VAO, ���� �������� �� ���������
		glBindVertexArray(0);

		// �������� ���������� ������
		VertexCount = 3;
	}

	// ������� �������������
	glBindVertexArray(VAO_Index);
	glDrawArrays(GL_TRIANGLES, 0, 8);
}