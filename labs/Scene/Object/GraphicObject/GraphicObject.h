#pragma once

#include "../../../General_Heading.h"

using namespace std;
using namespace glm;

enum class GraphicObjectType {
	none, road, building,
	vehicle, big_nature, small_nature,
	big_prop, medium_prop, small_prop
};

//  À¿—— ƒÀﬂ –¿¡Œ“€ — √–¿‘»◊≈— »Ã Œ¡⁄≈ “ŒÃ
class GraphicObject
{
public:
	GraphicObject();

	void setColor(vec4& color);
	void setPosition(vec3& position);
	void setAngle(float degree);
	void setType(GraphicObjectType type);
	void setDimensions(vec3& dimensions);

	void setMeshId(int id);
	void setTextureId(int id);
	void setMaterialId(int id);

	vec4 getColor();
	vec3 getPosition();
	float getAngle();
	GraphicObjectType getType();
	vec3& getDimensions();
	mat4& getModelMatrix();

	int getMeshId();
	int getTextureId();
	int getMaterialId();

	int getMeshIdConst() const {
		return meshId;
	}
	int getTextureIdConst() const {
		return textureId;
	}
	int getMaterialIdConst() const {
		return materialId;
	}

private:
	vec4 color;
	GraphicObjectType type;
	vec3 dimensions;
	vec3 position;
	float angle;

	int meshId;
	int textureId;
	int materialId;

	mat4 modelMatrix;
};
