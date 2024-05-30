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

void RenderManager::init()
{
	// Здесь происходит инициализация объекта RenderManager после инициализации OpenGL
	// загрузка шейдеров, установка параметров и т.д.
	Shader shader;
	shader.load("Data//SHADERS//DiffuseTextureInstanced.vsh", "Data//SHADERS//DiffuseTextureInstanced.fsh");
	shaders.push_back(shader);

}

void RenderManager::start()
{
	// очистка буфера кадра
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включение теста глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);

	// активация шейдера
	shaders[0].activate();
	// устанавливаем матрицу проекции
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shaders[0].setUniform("projectionMatrix", projectionMatrix);

	//устанавливаем параметры света
	shaders[0].setUniform("lAmbient", light->getAmbient());
	shaders[0].setUniform("lDiffuse", light->getDiffuse());
	shaders[0].setUniform("lSpecular", light->getSpecular());
	shaders[0].setUniform("lPosition", light->getDirection());

	//очистка вектора объектов
	graphicObjects.clear();

}

void RenderManager::setCamera(Camera* camera)
{
	this->camera = camera;
}

void RenderManager::setLight(Light* light)
{
	this->light = light;
}

void RenderManager::addToRenderQueue(GraphicObject& graphicObject)
{
	this->graphicObjects.push_back(graphicObject);
}

void RenderManager::finish()
{
	materialChanged = 0;
	textureChanged = 0;
	drawCallCount = 0;

	// получаем матрицу камеры
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

		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		int meshId = graphicObject.getMeshId();
		if (prevMeshId != meshId) {
			draw(modelMatrices, shaders, prevMeshId);
			prevMeshId = meshId;
		}
		// устанавливаем матрицу наблюдения модели
		modelMatrices.push_back(modelViewMatrix);
		if (modelMatrices.size() >= 20) {
			draw(modelMatrices, shaders, prevMeshId);
		}
	}
	Texture::disableAll();
}

string RenderManager::getRenderDescription()
{
	return "[Material changed: " + to_string(materialChanged) +
		"][Texture changed: " + to_string(textureChanged) +
		"][Draw calls: " + to_string(drawCallCount) + "]";
}