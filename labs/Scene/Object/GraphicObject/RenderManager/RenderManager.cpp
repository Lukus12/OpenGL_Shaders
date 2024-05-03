#include "RenderManager.h"

void RenderManager::init()
{
	// Здесь происходит инициализация объекта RenderManager после инициализации OpenGL
	// загрузка шейдеров, установка параметров и т.д.
	
	// загрузка шейдера
	shader.load("Data//SHADER//Example.vsh", "Data//SHADER/Example.fsh");
}

void RenderManager::start()
{
	// очистка вектора графических объектов
	graphicObjects.clear();

	// отчищаем буфер кадра
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины (на всякий случай)
	glEnable(GL_DEPTH_TEST);

	// вывод полигонов в виде линий с отсечением нелицевых граней
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
	// активируем шейдер, используемый для вывода объекта
	shader.activate();
	// устанавливаем матрицу проекции
	mat4& projectionMatrix = camera->getProjectionMatrix();
	shader.setUniform("projectionMatrix", projectionMatrix);
	// получаем матрицу камеры
	mat4& viewMatrix = camera->getViewMatrix();
	// выводим все объекты
	for (auto& graphicObject : graphicObjects) {
		// устанавливаем матрицу наблюдения модели
		mat4 modelViewMatrix = viewMatrix * graphicObject.getModelMatrix();
		shader.setUniform("modelViewMatrix", modelViewMatrix);

		// устанавливаем текстуру (привязываем к текстурному блоку)
		int textureId = graphicObject.getTextureId();
		Texture* texture = ResourceManager::instance().getTexture(textureId);
		if (texture != nullptr) texture->bind(GL_TEXTURE0);

		// uniform-переменная texture_0 связанна с нулевым текстурным блоком 
		shader.setUniform("texture_0", 0);

		// выводим меш
		int meshId = graphicObject.getMeshId();
		Mesh* mesh = ResourceManager::instance().getMesh(meshId);
		if (mesh != nullptr) mesh->draw();
	}
}
