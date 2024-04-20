#pragma once

#include "../../General_Heading.h"

#include "..\Object\GraphicObject\GraphicObject.h"

// �����-������������ ��� �������� ����������� �����������
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };


// ����� ��� ������������� �������� �������
class GameObject
{
public:
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(shared_ptr<GraphicObject> graphicObject);
	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
	void setPosition(int x, int y);
	void setPosition(int x, int y, float z);
	void setPosition(ivec2 position);
	// ��������� ������� ���������� ���������
	ivec2 getPosition();

	// ������ �������� � ��������� ����������� � ��������� ��������� 
	// �������� ������������ ������������ ����������� ������ � �������
	void move(MoveDirection direction, float speed = 3.0f);
	// �������� �� ��, ��� ������ � ��������� ������ ��������
	bool isMoving();
	// ��������� �������� ������� (������� ����������� �������)
	// ����� ���������� ���������� � ������� simulation
	void simulate(float sec);

	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	shared_ptr<GraphicObject> graphicObject;
	// ��������� ������� (�������� ����������� �����������)
	MoveDirection sost;
	// �������� � ����������� (�� 0.0 �� 1.0)
	float progress;
	// �������� ����������� (������/���)
	float speed;
};