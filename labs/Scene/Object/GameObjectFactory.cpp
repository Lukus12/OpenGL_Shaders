#include "GameObjectFactory.h"

using namespace std;
using namespace glm;
using namespace rapidjson;

void GameObjectFactory::init(std::string filename)
{
	MaterialParams materialchik{};
	vec4 color = {};
	float val = 0;
	ifstream f(filename);
	if (!f.is_open()) {
		cout << "Fail!\n";
	}
	// загружаем весь исходный текст (до разделителя - нулевого символа)
	//cout << "Pars " << filename << ":\n";

	string typeMaterial;
	string textureMaterial;

	string jsonString;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	// выводим считанную строку для отладки
	//cout << jsonString << endl;
	// парсим - если ошибка, то выходим
	Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		cout << "Invalid file format!\n";
	}
	
	for (auto& member : document.GetObject()) {
		//cout << member.name.GetString() << " : \n";
		//string nameType = member.name.GetString();
		if (member.value.IsObject()) {
			for (auto itr = member.value.MemberBegin(); itr != member.value.MemberEnd(); ++itr) {
				//cout << itr->name.GetString() << " : ";
				if (itr->value.IsString()) {
					shared_ptr<Mesh> mesh = make_shared<Mesh>();
					mesh->load(itr->value.GetString());
					meshes.push_back(mesh);
					//cout << "mesh load\n";
				}
				else {
					if (itr->value.IsObject()) {
						//cout << endl;
						for (auto materialValue = itr->value.MemberBegin(); materialValue != itr->value.MemberEnd(); ++materialValue) {
							//cout << materialValue->name.GetString() << " : ";
							if (materialValue->value.IsString()) {
								string nameTypeMaterial = materialValue->name.GetString();
								if (nameTypeMaterial == "type") {
									typeMaterial = materialValue->value.GetString();
								}
								if (nameTypeMaterial == "texture") {
									textureMaterial = materialValue->value.GetString();
								}
							}
							if (materialValue->value.IsArray()) {
								//cout << materialValue->name.GetString() << " : ";
								string nameParamsMaterial = materialValue->name.GetString();
								//cout << nameTypeMaterial << " : ";
								if (nameParamsMaterial != "shininess") {
									color[0] = materialValue->value[0].GetFloat();
									color[1] = materialValue->value[1].GetFloat();
									color[2] = materialValue->value[2].GetFloat();
									color[3] = materialValue->value[3].GetFloat();
									if (nameParamsMaterial == "diffuse") {
										materialchik.Diffuse = color;
									}
									if (nameParamsMaterial == "ambient") {
										materialchik.Ambient = color;
									}
									if (nameParamsMaterial == "specular") {
										materialchik.Specular = color;
									}
									if (nameParamsMaterial == "emission") {
										materialchik.Emission = color;
									}
									color = {};
								}
							}
							if(materialValue->value.IsFloat()) {
								materialchik.Shininess = materialValue->value.GetFloat();
								// указатель на базовый класс материала
								if (typeMaterial == "PhongMaterialWithTexture") {
									shared_ptr<Texture> TextureObj = make_shared<Texture>();
									TextureObj->load(textureMaterial);

									shared_ptr<PhongMaterialWithTexture> material = make_shared<PhongMaterialWithTexture>();
									material->load(materialchik);
									material->setTexture(TextureObj);
									materials.push_back(material);
								}
								if (typeMaterial == "PhongMaterial") {
									shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
									material->load(materialchik);
									materials.push_back(material);
								}
								
							}
							//cout << endl;
						}
						//cout << endl<< endl;
					}
				}
			}
		}
	}
}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, int z)
{
	int index{};
	switch (type)
	{
	case GameObjectType::BOMB:
		index = 4;
		break;
	case GameObjectType::BORDER_OBJECT:
		index = 2;
		break;
	case GameObjectType::HEAVY_OBJECT:
		index = 1;
		break;
	case GameObjectType::LIGHT_OBJECT:
		index = 0;
		break;
	case GameObjectType::MONSTER:
		index = 5;
		break;
	case GameObjectType::PLAYER:
		index = 3;
		break;
	}
	
	shared_ptr<GraphicObject> GrafObj = shared_ptr<GraphicObject>(new GraphicObject());
	GrafObj->setMaterial({ materials[index] });
	GrafObj->setMesh(meshes[index]);
	graphicObjects.push_back(GrafObj);

	shared_ptr<GameObject> GameObj(new GameObject);
	(*GameObj).setGraphicObject(graphicObjects.back());
	(*GameObj).setPosition(vec3(x, y, z));

	return GameObj;
}

