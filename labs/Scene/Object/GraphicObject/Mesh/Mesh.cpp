#include "..\Mesh\Mesh.h"


using namespace std;
using namespace glm;

void Mesh::load(string filename)
{
	// вектор для хранения геометрических координат
	vector<vec3> vec;
	// вектор для хранения нормалей
	vector<vec3> normal;
	// вектор для хранения текстурных координат
	vector<vec2> textura;
	// вектор для хранения индексов атрибутов, для построения вершин
	vector<ivec3> fPoints;
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	map<string, int> vertexToIndexTable;
	// массив вершин полигональной сетки
	vector<Vertex> vertices;
	// массив индексов
	vector<GLuint> indices;

	int index = 0;

	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Failed!\n";
	}
	else {
		string str;
		vec3 cord{};
		vec2 cord2{};
		while (getline(fin, str)) {

			if (str[0] != '#' and str[0] != '\n' and str[0] != 'f' and str[0] != 'g') {
				istringstream strNew(str);
				string view;

				strNew >> view;
				if (view == "v") {
					strNew >> cord[0] >> cord[1] >> cord[2];
					//cout << cord[0] << " " << cord[1] << " " << cord[2] << endl;
					vec.push_back(cord);
				}
				if (view == "vn") {
					strNew >> cord[0] >> cord[1] >> cord[2];
					normal.push_back(cord);
				}
				if (view == "vt") {
					strNew >> cord2[0] >> cord2[1];
					textura.push_back(cord2);
				}
			}
			if (str[0] == 'f') {
				ivec3 fCord{};
				string simbol = "";
				int k = 0;
			
				istringstream strNew(str);
				string strSub;
				for (int i = 0; i < 3; i++) {
					strNew >> strSub;
					if(strSub[0] == 'f') strNew >> strSub;
					//cout << strSub << endl;
					auto iterator = vertexToIndexTable.find(strSub);
					if (iterator == vertexToIndexTable.end()) {
						vertexToIndexTable[strSub] = index;
						indices.push_back(index);
						
						replace(strSub.begin(), strSub.end(), '/', ' ');
						//cout << strSub << endl;
						istringstream subSubSr(strSub);
						subSubSr >> fCord[0] >> fCord[1] >> fCord[2];
						//cout << endl;
						//cout << fCord[0] << " " << fCord[1] << " " << fCord[2] << endl;
						fPoints.push_back(fCord);
						
						
						index++;
					}
					else {
						int pastIndex = (*iterator).second;
						indices.push_back(pastIndex);
					}
				}
				//cout << endl;
				
			}
		}
		fin.close();
	}


	for (int i = 0; i < fPoints.size(); i++) {
		Vertex memberVertices;
		int indexVec = fPoints[i][0] - 1;
		int indexTextura = fPoints[i][1] - 1;
		int indexNormal = fPoints[i][2] - 1;
		for (int j = 0; j < 3; j++) {
			memberVertices.coord[j] = vec[indexVec][j];
			memberVertices.normal[j] = normal[indexNormal][j];
		}
		for (int j = 0; j < 2; j++) {
			memberVertices.texCoord[j] = textura[indexTextura][j];
		}
		vertices.push_back(memberVertices);
	}

	indexCount = indices.size();

	//этап загрузки буфферов
	glGenBuffers(1, &bufferIds[0]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &bufferIds[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::draw(){

	//Этап использования буфферов
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}