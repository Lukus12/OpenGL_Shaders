#pragma once
#include "../../General_Heading.h"

using namespace glm;
using namespace std;

struct MaterialParams {
	vec4 Diffuse;
	vec4 Ambient;
	vec4 Specular;
	vec4 Emission;
	float Shininess;
};