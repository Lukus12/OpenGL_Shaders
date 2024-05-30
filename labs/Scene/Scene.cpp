#include "Scene.h"
#define DRAW_RANGE_COEF 1

Scene::Scene()
{
	this->camera = nullptr;
	this->light = nullptr;
}

void Scene::init(std::string filename)
{
	fstream File(filename);
	if (!File) {
		cout << filename << " ошибка\n";
		return;
	}

	string line;
	getline(File, line, static_cast<char>(0));
	File.close();

	this->document.Parse(line.c_str());
	if (document.GetParseError() != 0) {
		cout << "Ошибка парсера!\n";
		return;
	}
}

bool Scene::loadFromJson(std::string filename)
{
	fstream File(filename);
	if (!File) {
		cout << filename << " ошибка\n";
		return false;
	}

	string line;
	getline(File, line, static_cast<char>(0));
	File.close();

	rapidjson::Document sceneDesc;
	sceneDesc.Parse(line.c_str());
	if (sceneDesc.GetParseError() != 0) {
		cout << "Ошибка парсера!\n";
		return false;
	}

	for (auto& objDesc : sceneDesc.GetArray()) {
		string model = objDesc["model"].GetString();
		auto posArr = objDesc["position"].GetArray();

		vec3 position;
		for (int i = 0; i < 3; i++) {
			position[i] = posArr[i].GetFloat();
		}
		float angle = objDesc["angle"].GetFloat();

		GraphicObject object;
		object = createGraphicObject(model);
		object.setPosition(position);
		object.setAngle(angle);
		graphicObjects.push_back(object);
	}
	return true;
}

void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

void Scene::setLight(Light* light)
{
	this->light = light;
}

void Scene::draw()
{
	renderedObjectCount = 0;
	mat4 camMatrix = camera->getProjectionMatrix() * camera->getViewMatrix();

	for (auto& grObj : graphicObjects) {
		if (!lodTest(grObj)) continue;
		if (!frustumCullingTest(grObj, camMatrix)) continue;

		renderedObjectCount++;
		RenderManager::instance().addToRenderQueue(grObj);
	}
}

std::string Scene::getSceneDescription()
{
	return "[" + to_string(renderedObjectCount) +
		   "/" + to_string(graphicObjects.size()) + " objects rendered] ";
}

GraphicObject Scene::createGraphicObject(std::string model)
{
	GraphicObject newObject;
	if (document.HasMember(model.c_str())) {
		string type = document[model.c_str()]["type"].GetString();
		string objectTypes[] = { "none", "road", "building",
								 "vehicle", "big nature", "small nature",
								 "big prop", "medium prop", "small prop" };

		bool flag = true;
		int typeNumber = 0;
		while (flag) {
			if (objectTypes[typeNumber] == type) {
				flag = false;
			}
			else {
				typeNumber++;
			}
		}

		const rapidjson::Value& dimension_array = document[model.c_str()]["dimensions"];
		vec3 dimension{};
		assert(dimension_array.IsArray());
		for (int i = 0; i < 3; i++) {
			dimension[i] = dimension_array[i].GetDouble();
		}

		string mesh = document[model.c_str()]["mesh"].GetString();
		string texture = document[model.c_str()]["texture"].GetString();
		string material = document[model.c_str()]["material"].GetString();

		ResourceManager& rm = ResourceManager::instance();
		int meshId = rm.loadMesh(mesh);
		int textureId = rm.loadTexture(texture);
		int materialId = rm.loadMaterial(material);

		newObject.setType(static_cast<GraphicObjectType>(typeNumber));
		newObject.setDimensions(dimension);
		newObject.setMeshId(meshId);
		newObject.setTextureId(textureId);
		newObject.setMaterialId(materialId);
	}
	return newObject;
}

bool Scene::lodTest(GraphicObject& graphicObject)
{
	vec3 objPos = graphicObject.getPosition();
	vec3 camPos = camera->getCameraPosition();
	vec3 vect = camPos - objPos;

	float distance = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z) * DRAW_RANGE_COEF;

	switch (graphicObject.getType())
	{
	case GraphicObjectType::none:
		return true;

	case GraphicObjectType::road:
		return true;

	case GraphicObjectType::building:
		return true;
	
	case GraphicObjectType::vehicle:
		if (distance <= 500) 
			return true;
		else 
			return false;
	
	case GraphicObjectType::big_nature:
		if (distance <= 350) 
			return true;
		else 
			return false;
	
	case GraphicObjectType::small_nature:
		if (distance <= 200) 
			return true;
		else 
			return false;
	
	case GraphicObjectType::big_prop:
		if (distance <= 400) 
			return true;
		else 
			return false;
	
	case GraphicObjectType::medium_prop:
		if (distance <= 300) 
			return true;
		else 
			return false;
	
	case GraphicObjectType::small_prop:
		if (distance <= 200) 
			return true;
		else 
			return false;
	
	default:
		break;
	}
}

bool Scene::frustumCullingTest(GraphicObject& graphicObject, mat4& matr)
{
	mat4 PVM = matr * graphicObject.getModelMatrix();
	vec3 dimensions = graphicObject.getDimensions();
	vec4 vertices[] = {
		vec4(+dimensions.x / 2,+dimensions.y / 2, +dimensions.z / 2, 1.0),
		vec4(+dimensions.x / 2,+dimensions.y / 2, -dimensions.z / 2, 1.0),
		vec4(+dimensions.x / 2,-dimensions.y / 2, +dimensions.z / 2, 1.0),
		vec4(+dimensions.x / 2,-dimensions.y / 2, -dimensions.z / 2, 1.0),
		vec4(-dimensions.x / 2,+dimensions.y / 2, +dimensions.z / 2, 1.0),
		vec4(-dimensions.x / 2,+dimensions.y / 2, -dimensions.z / 2, 1.0),
		vec4(-dimensions.x / 2,-dimensions.y / 2, +dimensions.z / 2, 1.0),
		vec4(-dimensions.x / 2,-dimensions.y / 2, -dimensions.z / 2, 1.0),
	};

	vec4 newVertices[8];
	for (int i = 0; i < 8; i++) {
		newVertices[i] = PVM * vertices[i];
	}

	bool flag = 0;
	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].x > newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;
	flag = 0;

	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].x < -newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;
	flag = 0;

	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].y > newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;
	flag = 0;

	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].y < -newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;
	flag = 0;

	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].z > newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;
	flag = 0;

	for (int i = 0; i < 8; i++) {
		if ((newVertices[i].z < -newVertices[i].w))
			flag = flag || 0;
		else
			flag = flag || 1;
	}
	if (!flag)
		return false;

	return true;
}