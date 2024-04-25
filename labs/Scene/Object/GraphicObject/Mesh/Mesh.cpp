#include "Mesh.h"


using namespace std;
using namespace glm;

Mesh::Mesh()
{
	// количество индексов (вершин в меше)
	indexCount = {};
	// Глобальная переменная для хранения идентификатора VAO-объекта (индекс VAO-объекта)
	VAO = {};
	// индекс VBO-буфера вершин
	vertexVAOBuffer = {};
	// индекс VBO-буфера индексов
	indexVAOBuffer = {};
}

void Mesh::load(string filename)
{
	// вектор для хранения геометрических координат
	vector<vec3> vec;
	// вектор для хранения нормалей
	vector<vec3> normalLocal;
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
		cout << "Failed Way!\n";
		return;
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
					normalLocal.push_back(cord);
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
			memberVertices.normal[j] = normalLocal[indexNormal][j];
		}
		for (int j = 0; j < 2; j++) {
			memberVertices.texCoord[j] = textura[indexTextura][j];
		}
		vertices.push_back(memberVertices);
	}

	indexCount = indices.size();

	//этап загрузки буфферов

	//Создание и привязка VAO-объекта
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Создание и инициализация буфера вершин. 
	glGenBuffers(1, &vertexVAOBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVAOBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// Создание буфера индексов
	glGenBuffers(1, &indexVAOBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVAOBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//Указание места и формата хранения атрибутов вершин

	// Устанавливаем атрибут для позиции вершин
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glEnableVertexAttribArray(0);

	// Устанавливаем атрибут для нормалей
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// Устанавливаем атрибут для текстурных координат
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);


	// «Отвязка» VAO-объекта
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return;
}

void Mesh::draw(){
	//Привыязка VAO-объекта
	glBindVertexArray(VAO);
	//Вызов команды отрисовки полигонов
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	//«Отвязка» VAO-объекта
	glBindVertexArray(0);
}